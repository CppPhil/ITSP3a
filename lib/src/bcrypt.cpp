#include "bcrypt.hpp"
#include "binary_io.hpp" // itsp3::openFileForBinaryReading, itsp3::openFileForBinaryWriting
#include "log.hpp"                       // ITSP3_LOG
#include "print_bytes_as_ascii.hpp"      // itsp3::PrintBytesAsAscii
#include "record.hpp"                    // itsp3::Record
#include "string_scrubber.hpp"           // itsp3::StringScrubber
#include <ciso646>                       // not, or, and
#include <iterator>                      // std::begin, std::end
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::copy
#include <pl/print_bytes_as_hex.hpp>     // pl::print_bytes_as_hex
#include <string>                        // std::string

namespace itsp3 {
namespace {
/*!
 * \brief The size of the username and hash parts of the records written
 *        and read from the binary file.
 * \note A username may not be larger than 'maxSize'.
 **/
constexpr const std::size_t maxSize = BCRYPT_HASHSIZE;
} // anonymous namespace

Bcrypt::Bcrypt(std::string filePath)
  : m_filePath{std::move(filePath)}, m_salt{}, m_hash{}
{
  ITSP3_LOG << "Created Bcrypt object\n"
            << "filepath: " << m_filePath;
}

AddUserResult Bcrypt::addUser(
  std::string_view username,
  std::string_view password)
{
#ifdef ENABLE_PW_CHECKS
  const PasswordCheckingResult passwordCheckingResult{
    checkPassword(username, password)};

  if (passwordCheckingResult != PasswordCheckingResult::Ok) {
    return AddUserResult{passwordCheckingResult};
  }
#endif // ENABLE_PW_CHECKS

  if (not isLengthOk(username)) {
    return AddUserResult{
      AddUserResult::Value::Failure, "Username was too long"};
  }

  if (not isLengthOk(password)) {
    return AddUserResult{
      AddUserResult::Value::Failure, "Password was too long"};
  }

  ITSP3_LOG << "username: \"" << username << "\"\n"
            << "password: \"" << password << '"';

  // The optional will be set if a hash could be found for the username
  std::optional<std::string> hashOpt{findHashOfUser(username)};

  // if the user was already there -> exit with failure
  if (hashOpt) {
    ITSP3_LOG << "Found hash for user \"" << username << "\", returning false.";
    return AddUserResult{
      AddUserResult::Value::Failure, "User was already there."};
  }

  std::fstream fs{}; // the filestream used to write to the file

  // if the file could not be opened -> exit with failure
  if (not openFileForBinaryWriting(fs, m_filePath)) {
    ITSP3_LOG << "Failed to open filestream, path: \"" << m_filePath << '"';
    return AddUserResult{
      AddUserResult::Value::Failure, "Could not open binary file."};
  }

  // note that the file stream is opened in append mode by
  // 'openFileForBinaryWriting'.

  int ret // note that 'ret' is used for the error codes returned by bcrypt
    = bcrypt_gensalt(s_defaultSaltWorkfactor, m_salt.data());

  if (ret != 0) {
    ITSP3_LOG << "Failed to generate salt.";
    return AddUserResult{
      AddUserResult::Value::Failure, "Could not generate salt."};
  }

  ITSP3_LOG << "Generated salt.\n"
            << "hex:   " << pl::print_bytes_as_hex{m_salt.data(), m_salt.size()}
            << '\n'
            << "ASCII: " << PrintBytesAsAscii{m_salt.data(), m_salt.size()};

  std::string hashInput{std::string{username} + std::string{password}};

  // 'hashInput' memory shall be zeroed out on scope exit
  // as it does contain the password
  StringScrubber hashInputScrubber{hashInput};

  ITSP3_LOG << "The concatenation of username and password (hashInput) is:\n"
            << "hex:   "
            << pl::print_bytes_as_hex{hashInput.data(), hashInput.size()}
            << '\n'
            << "ASCII: "
            << PrintBytesAsAscii{hashInput.data(), hashInput.size()};

  // bcrypt_hashpw expects the first argument to be a null-terminated string
  ret = bcrypt_hashpw(hashInput.data(), m_salt.data(), m_hash.data());

  if (ret != 0) {
    ITSP3_LOG << "Failed to hash the hashInput!";
    return AddUserResult{
      AddUserResult::Value::Failure, "Could not generate hash."};
  }

  ITSP3_LOG << "Created hash of the hashInput\n"
            << "hex:   " << pl::print_bytes_as_hex{m_hash.data(), m_hash.size()}
            << '\n'
            << "ASCII: " << PrintBytesAsAscii{m_hash.data(), m_hash.size()};

  const Record recordToWrite{
    std::string{username}, std::string(std::begin(m_hash), std::end(m_hash))};

  const bool couldWriteData{static_cast<bool>(recordToWrite.write(fs))};

  if (couldWriteData) {
    return AddUserResult{AddUserResult::Value::Success, "Success"};
  }

  return AddUserResult{
    AddUserResult::Value::Failure, "Failed to write to binary file."};
}

bool Bcrypt::checkPasswordValidity(
  std::string_view username,
  std::string_view password)
{
  // find the hash for 'username'. If there is no 'username' in the binary
  // file the optional will be a nullopt
  std::optional<std::string> hashOpt{findHashOfUser(username)};

  ITSP3_LOG << "username: \"" << username << '"' << '\n'
            << "password: \"" << password << '"';

  // if there is no user 'username' -> exit with failure.
  if (not hashOpt) {
    ITSP3_LOG << "no hash found for username: \"" << username << '"';
    return false;
  }

  // create the hash input to hash and then have it be checked against the
  // hash read from the file using 'findHashOfUser'
  std::string input{std::string{username} + std::string{password}};

  // zero out the memory of the hash input as it does contain the password
  StringScrubber inputScrubber{input};

  ITSP3_LOG << "input: (username + password)\n"
            << "hex:   " << pl::print_bytes_as_hex{input.data(), input.size()}
            << '\n'
            << "ASCII: " << PrintBytesAsAscii{input.data(), input.size()};

  const std::string hash{*hashOpt}; // get the hash read from the file.

  ITSP3_LOG << "hash\n"
            << "hex:   " << pl::print_bytes_as_hex{hash.data(), hash.size()}
            << '\n'
            << "ASCII: " << PrintBytesAsAscii{hash.data(), hash.size()};

  const int ret{bcrypt_checkpw(input.data(), hash.data())};

  return ret == 0; // will be true if the hash input matches with the hash
                   // read from the binary file after having hashed the
                   // hash input
}

std::optional<std::string> Bcrypt::findHashOfUser(std::string_view username)
{
  std::fstream fs{}; // filestream to read with.

  ITSP3_LOG << "input:\n"
            << "hex:   "
            << pl::print_bytes_as_hex{username.data(), username.size()} << '\n'
            << "ASCII: " << PrintBytesAsAscii{username.data(), username.size()};

  if (not openFileForBinaryReading(fs, m_filePath)) {
    ITSP3_LOG << "Failed to open file for reading, returning nullopt";
    return std::nullopt;
  }

  Record currentRecord{};

  while (Record::read(fs, &currentRecord)) {
    if (currentRecord.getUsername() == username) { // it's the same username
      return std::make_optional(std::string{currentRecord.getHash()});
    }
  }

  ITSP3_LOG << "Username \"" << username << '"' << " was never found "
            << "in the binary file.";
  return std::nullopt; // no hash found for username given
}

bool Bcrypt::isLengthOk(std::string_view str) noexcept
{
  // usernames and paswords shall not be larger than 'maxSize'
  return str.size() <= maxSize;
}

const int Bcrypt::s_defaultSaltWorkfactor = 12;
} // namespace itsp3
