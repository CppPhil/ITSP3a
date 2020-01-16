#include "record.hpp"
#include "binary_io.hpp" // itsp3::readBinary
#include <ciso646>       // not
#include <climits>       // UCHAR_MAX
#include <istream>       // std::istream
#include <ostream>       // std::ostream
#include <pl/byte.hpp>   // pl::byte
#include <utility>       // std::move

namespace itsp3 {
std::istream& Record::read(std::istream& is, Record* outParam)
{
  PL_DBG_CHECK_PRE(outParam != nullptr);

  // read one byte, the size of the following username.
  pl::byte usernameByteSize{};
  if (not readBinary(is, &usernameByteSize, sizeof(usernameByteSize))) {
    return is; // return on read failure, as 'usernameByteSize' would
               // contain an invalid value.
  }

  // read the username.
  std::string usernameBuffer(
    static_cast<std::string::size_type>(usernameByteSize), ' ');
  if (not readBinary(is, &usernameBuffer[0U], usernameBuffer.size())) {
    return is;
  }

  // read one byte, the size of the following hash.
  pl::byte hashByteSize{};
  if (not readBinary(is, &hashByteSize, sizeof(hashByteSize))) {
    return is; // return on read failure, as 'hashByteSize' would
               // contain an invalid value.
  }

  // read the hash.
  std::string hashBuffer(
    static_cast<std::string::size_type>(hashByteSize), ' ');
  if (not readBinary(is, &hashBuffer[0U], hashBuffer.size())) {
    return is;
  }

  // write the data extracted to the output parameter.
  *outParam = Record{std::move(usernameBuffer), std::move(hashBuffer)};

  return is;
}

Record::Record() noexcept : Record{"", ""} // delegate to the binary constructor
{
}

Record::Record(std::string username, std::string hash)
  : m_username{std::move(username)}, m_hash{std::move(hash)}
{
  if (m_username.size() > UCHAR_MAX) {
    PL_THROW_WITH_SOURCE_INFO(
      TooLongStringForRecordException, "username was too long");
  }

  if (m_hash.size() > UCHAR_MAX) {
    PL_THROW_WITH_SOURCE_INFO(
      TooLongStringForRecordException, "hash was too long");
  }
}

std::ostream& Record::write(std::ostream& os) const
{
  const pl::byte     usernameByteSize{static_cast<pl::byte>(m_username.size())};
  const std::string& username{m_username};
  const pl::byte     hashByteSize{static_cast<pl::byte>(m_hash.size())};
  const std::string& hash{m_hash};

  writeBinary(os, &usernameByteSize, sizeof(usernameByteSize));
  writeBinary(os, username.data(), username.size());
  writeBinary(os, &hashByteSize, sizeof(hashByteSize));
  writeBinary(os, hash.data(), hash.size());

  return os;
}

std::string_view Record::getUsername() const noexcept
{
  return m_username;
}

std::string_view Record::getHash() const noexcept
{
  return m_hash;
}
} // namespace itsp3
