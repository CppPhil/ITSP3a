#include "check_password.hpp"
#include "alphabets.hpp"                 // itsp3::makeAlphabet
#include "log.hpp"                       // ITSP3_LOG
#include <ciso646>                       // not
#include <cstddef>                       // std::size_t
#include <ostream>                       // std::ostream
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::any_of
#include <pl/assert.hpp>                 // PL_ASSERT
#include <sstream>                       // std::ostringstream

namespace itsp3 {
namespace {
/*!
 * All the lower case character. (Assuming ASCII implementation).
 * '{' is the character after 'z'. (Note the use of half open ranges typical
 * in C++).
 * See an ASCII chart for reference at:
 * http://en.cppreference.com/w/cpp/language/ascii
 **/
constexpr std::array<char, '{' - 'a'> lowerCaseCharacters
  = makeAlphabet<'a', '{'>();

/*!
 * The upper case characters.
 **/
constexpr std::array<char, '[' - 'A'> upperCaseCharacters
  = makeAlphabet<'A', '['>();

/*!
 * The numbers '0' - '9' as chars.
 **/
constexpr std::array<char, ':' - '0'> numbers = makeAlphabet<'0', ':'>();

/*!
 * The 'special' characters.
 * pl::cont::make_array is used to deduce the size of the std::array
 **/
constexpr auto specialCharacters = ::pl::cont::make_array(
  ' ',
  '!',
  '"',
  '#',
  '$',
  '%',
  '&',
  '\'',
  '(',
  ')',
  '*',
  '+',
  ',',
  '-',
  '.',
  '/',
  ':',
  ';',
  '<',
  '=',
  '>',
  '?',
  '@',
  '[',
  '\\',
  ']',
  '^',
  '_',
  '`',
  '{',
  '|',
  '}',
  '~');

/*!
 * \brief Module local function to check if 'c' is a lower case character.
 * \param c The character to check.
 * \return true if 'c' is considered a lower case character, otherwise false.
 * \note These function are used in place of the (C) functions exported by the
 *       <cctype> header, as those include some (stupid) assertions on some
 *       implementations if the character supplied is outside of the range
 *       of ASCII characters 0x00 through 0x7F (both inclusive) as chars
 *       being byte sized object can hold values of the range 0x00 through
 *       0xFF (both inclusive) (assuming CHAR_BIT == 8, that is bytes being
 *       8 bit large). These funny assertion cause the application to crash
 *       on bad input, which is just ridiculous.
 **/
bool isLowerCase(char c) noexcept
{
  return pl::algo::any_of(lowerCaseCharacters, [c](char lowerCaseChar) {
    return lowerCaseChar == c;
  });
}

/*!
 * \brief Module local function to check if 'c' is an upper case character.
 * \param c The character to check.
 * \return true if 'c' is an upper case character, false otherwise.
 **/
bool isUpperCase(char c) noexcept
{
  return pl::algo::any_of(upperCaseCharacters, [c](char upperCaseChar) {
    return upperCaseChar == c;
  });
}

/*!
 * \brief Module local function to check if 'c' is a 'number' that is
 *        'c' compares equal to '0', '1', '2', '3', '4', '5', '6', '7',
 *        '8', or '9'.
 * \param c The characeter to check.
 * \return true if 'c' is considered to be a 'number', false otherwise.
 **/
bool isNumber(char c) noexcept
{
  return pl::algo::any_of(numbers, [c](char number) { return number == c; });
}

/*!
 * \brief Module local function to check if 'c' is a 'special' character,
 *        that is 'c' compares equal to either ' ', '!', '"', '#', '$', '%',
 *        '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';',
 *        '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{',
 *        '|', '}', or '~'
 * \param c The character to check.
 * \return true if 'c' is considered to be a special character, otherwise
 *         false.
 **/
bool isSpecialCharacter(char c) noexcept
{
  return pl::algo::any_of(specialCharacters, [c](char specialCharacter) {
    return specialCharacter == c;
  });
}

/*!
 * \brief Module local function to check if the password given is
 *        at least 8 characters long.
 * \param password The password to check.
 * \return true if the password is considered to be long enough,
 *         otherwise false.
 **/
bool isPasswordLengthOk(std::string_view password) noexcept
{
  static constexpr std::size_t minimumPasswordLength{8U};

  return password.size() >= minimumPasswordLength;
}

/*!
 * \brief Module local function to check if 'password' contains a lower case
 *        character.
 * \param password The password to check.
 * \return true if 'password' contains 1 or more lower case characters,
 *         otherwise false.
 **/
bool containsLowerCaseCharacter(std::string_view password) noexcept
{
  return pl::algo::any_of(password, &isLowerCase);
}

/*!
 * \brief Module local function to check if 'password' contains an upper case
 *        character.
 * \param password The password to check.
 * \return true if 'password' contains 1 or more upper case characters,
 *         otherwise false.
 **/
bool containsUpperCaseCharacter(std::string_view password) noexcept
{
  return pl::algo::any_of(password, &isUpperCase);
}

/*!
 * \brief Module local function to check if 'password' contains at least one
 *        number.
 * \param password The password to check.
 * \return true if 'password' contains one or more numbers, otherwise false.
 **/
bool containsNumber(std::string_view password) noexcept
{
  return pl::algo::any_of(password, &isNumber);
}

/*!
 * \brief Module local function to check whether 'password' contains at least
 *        1 'special' character.
 * \param password The password to check.
 * \return true if 'password' contains one or more 'special' characters,
 *         otherwise false.
 **/
bool containsSpecialCharacter(std::string_view password) noexcept
{
  return pl::algo::any_of(password, &isSpecialCharacter);
}

/*!
 * \brief Module local function to check if a given password is equal to
 *        a given username.
 * \param password The password to be compared to the username.
 * \param username The username to be compared to the password.
 * \return true if 'password' considered equal to 'username', otherwise
 *         false.
 **/
bool isEqualToUsername(std::string_view password, std::string_view username)
{
  return password == username;
}
} // anonymous namespace

std::ostream& operator<<(
  std::ostream&          os,
  PasswordCheckingResult passwordCheckingResult)
{
  switch (passwordCheckingResult) {
  case PasswordCheckingResult::TooShort:
    return os << "The password must contain at least 8 characters.";
  case PasswordCheckingResult::TooFewLowerCaseCharacters:
    return os << "The password must contain at least 1 lowercase character.";
  case PasswordCheckingResult::TooFewUpperCaseCharacters:
    return os << "The password must contain at least 1 uppercase character.";
  case PasswordCheckingResult::TooFewNumbers:
    return os << "The password must contain at least 1 numeric character.";
  case PasswordCheckingResult::TooFewSpecialCharacters:
    os << "The password must contain at least 1 special character.\n"
          "Special characters include: ";
    for (char c : specialCharacters) {
      os << c << ' ';
    }
    return os;
  case PasswordCheckingResult::EqualToUsername:
    return os << "The password may not be equal to the username.";
  case PasswordCheckingResult::Ok:
    return os << "The password was accepted.";
  default:
    break;
  }

  // Control flow should never reach here!
  PL_ASSERT(false);
}

std::string asString(PasswordCheckingResult passwordCheckingResult)
{
  std::ostringstream oss{};
  oss << passwordCheckingResult;
  return oss.str();
}

PasswordCheckingResult checkPassword(
  std::string_view username,
  std::string_view password) noexcept
{
  if (not isPasswordLengthOk(password)) {
    ITSP3_LOG << "username: " << username << ", password: " << password
              << "\n\tpassword too short";
    return PasswordCheckingResult::TooShort;
  }

  if (not containsLowerCaseCharacter(password)) {
    ITSP3_LOG << "username: " << username << ", password: " << password
              << "\n\tpassword has too few lower case characters.";
    return PasswordCheckingResult::TooFewLowerCaseCharacters;
  }

  if (not containsUpperCaseCharacter(password)) {
    ITSP3_LOG << "username: " << username << ", password: " << password
              << "\n\tpassword has too few upper case characters.";
    return PasswordCheckingResult::TooFewUpperCaseCharacters;
  }

  if (not containsNumber(password)) {
    ITSP3_LOG << "username: " << username << ", password: " << password
              << "\n\tpassword has too few numbers.";
    return PasswordCheckingResult::TooFewNumbers;
  }

  if (not containsSpecialCharacter(password)) {
    ITSP3_LOG << "username: " << username << ", password: " << password
              << "\n\tpassword has too few special characters.";
    return PasswordCheckingResult::TooFewSpecialCharacters;
  }

  if (isEqualToUsername(password, username)) {
    ITSP3_LOG << "username: " << username << ", password: " << password
              << "\n\tpassword is equal to username.";
    return PasswordCheckingResult::EqualToUsername;
  }

  ITSP3_LOG << "username: " << username << ", password: " << password
            << "\n\tpassword was determined to be OK.";
  return PasswordCheckingResult::Ok;
}
} // namespace itsp3
