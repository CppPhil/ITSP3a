/*!
 * \file check_password.hpp
 * \brief Exports utilities for checking the 'strength' of a password.
**/
#ifndef INCG_ITSP3_CHECK_PASSWORD_HPP
#define INCG_ITSP3_CHECK_PASSWORD_HPP
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <iosfwd> // std::ostream

namespace itsp3
{
/*!
 * \brief Scoped enum type used as the result of the checkPassword function.
**/
enum class PasswordCheckingResult
{
    TooShort, /*!< The password did not contain at least 8 characters */
    TooFewLowerCaseCharacters, /*!< The password did not contain a lower case
                                *   character.
                               **/
    TooFewUpperCaseCharacters, /*!< The password did not contain an upper cas
                                *   character.
                               **/
    TooFewNumbers, /*!< The password did not contain a number. */
    TooFewSpecialCharacters, /*!< The password did not contain a
                               *  special character.
                              **/
    EqualToUsername, /*!< The password compares equal to the username. */
    Ok /*!< The password was determined to be acceptable */
};

/*!
 * \brief Prints extended information for a PasswordCheckingResult enumerator
 *        to an ostream.
 * \param os The ostream to print to.
 * \param passwordCheckingResult The enumerator to print.
 * \return A reference to 'os'.
 * \note Use boost::lexical_cast<std::string> to invoke this function
 *       in order to turn a PasswordCheckingResult enumerator into a std::string.
**/
std::ostream &operator<<(
    std::ostream &os,
    PasswordCheckingResult passwordCheckingResult);

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
    boost::string_ref username,
    boost::string_ref password) noexcept;
} // namespace itsp3
#endif // INCG_ITSP3_CHECK_PASSWORD_HPP
