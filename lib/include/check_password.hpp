/*!
 * \file check_password.hpp
 * \brief Exports utilities for checking the 'strength' of a password.
 **/
#ifndef INCG_ITSP3_CHECK_PASSWORD_HPP
#define INCG_ITSP3_CHECK_PASSWORD_HPP
#include <iosfwd>      // std::ostream
#include <string>      // std::string
#include <string_view> // std::string_view

namespace itsp3 {
/*!
 * \brief Scoped enum type used as the result of the checkPassword function.
 **/
enum class PasswordCheckingResult {
  TooShort, /*!< The password did not contain at least 8 characters */
  TooFewLowerCaseCharacters, /*!< The password did not contain a lower case
                              *   character.
                              **/
  TooFewUpperCaseCharacters, /*!< The password did not contain an upper cas
                              *   character.
                              **/
  TooFewNumbers,             /*!< The password did not contain a number. */
  TooFewSpecialCharacters,   /*!< The password did not contain a
                              *  special character.
                              **/
  EqualToUsername, /*!< The password compares equal to the username. */
  Ok               /*!< The password was determined to be acceptable */
};

/*!
 * \brief Prints extended information for a PasswordCheckingResult enumerator
 *        to an ostream.
 * \param os The ostream to print to.
 * \param passwordCheckingResult The enumerator to print.
 * \return A reference to 'os'.
 **/
std::ostream& operator<<(
  std::ostream&          os,
  PasswordCheckingResult passwordCheckingResult);

/*!
 * \brief Converts a PasswordCheckingResult enumerator to a std::string.
 * \param passwordCheckingResult The enumerator to convert.
 * \return A std::string containing the text representation of the
 *         PasswordCheckingResult enumerator.
 **/
std::string asString(PasswordCheckingResult passwordCheckingResult);

/*!
 * \brief Checks a password and returns the appropriate PasswordCheckingResult
 *        depending on the username and password supplied.
 * \param username The username to check the strength of the assoctiated
 *                 password of.
 * \param password The password of 'username' which shall be checked.
 * \return The resulting enumerator.
 * \note Only a return value of PasswordCheckingResult::Ok indicates success.
 **/
PasswordCheckingResult checkPassword(
  std::string_view username,
  std::string_view password) noexcept;
} // namespace itsp3
#endif // INCG_ITSP3_CHECK_PASSWORD_HPP
