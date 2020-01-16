#ifndef INCG_ITSP3_ADD_USER_RESULT_HPP
#define INCG_ITSP3_ADD_USER_RESULT_HPP
#include "check_password.hpp" // itsp3::PasswordCheckingResult
#include <iosfwd>             // std::ostream
#include <string>             // std::string
#include <string_view>        // std::string_view

namespace itsp3 {
/*!
 * \brief Type returned by the addUser non-static member function of type
 *        Bcrypt.
 **/
class AddUserResult {
public:
  using this_type = AddUserResult;

  /*!
   * \brief Nested scoped enum type acting as a more legible boolean
   *        representing failure or success.
   **/
  enum class Value {
    Failure, /*!< The user could not be added to the binary file. */
    Success  /*!< The user could be added to the binary file. */
  };

  /*!
   * \brief Creates an AddUserResult object from a PasswordCheckingResult
   *        enumerator returned by the checkPassword function.
   * \param passwordCheckingResult The enumerator to create the AddUserResult
   *                               from. The operator bool() non-static
   *                               member function will return true if this
   *                               enumerator is PasswordCheckingResult::Ok
   * \note The message returned by .getMessage() and printed by the
   *       associated operator<< will be the text printed by applying the
   *       operator<< to the PasswordCheckingResult passed in.
   * \see checkPassword
   **/
  explicit AddUserResult(PasswordCheckingResult passwordCheckingResult);

  /*!
   * \brief Binary constructor to 'manually' create AddUserResult object
   *        not created from a PasswordCheckingResult enumerator.
   * \param ok AddUserResult::Value::Failure if this AddUserResult shall
   *           indicate failure to add a new user to the binary file.
   *           Or AddUserResult::Value::Success if this AddUserResult shall
   *           indicate success to add a new user to the binary file.
   * \param message The message that shall be returned by the getMessage
   *                non-static member function and be printed to an
   *                ostream by the associated operator<< function.
   **/
  AddUserResult(Value ok, std::string message);

  /*!
   * \brief Explicit boolean conversion operator.
   * \return true if this object was constructed from
   *         PasswordCheckingResult::Ok or from AddUserResult::Value::Success
   *         and an arbitrary message.
   *         Otherwise false will be returned.
   **/
  explicit operator bool() const noexcept;

  /*!
   * \brief Returns a string_view to the message of this object.
   * \return A string_view to the message of this object.
   **/
  std::string_view getMessage() const noexcept;

private:
  bool        m_ok;      /*!< Whether or not this object indicates success */
  std::string m_message; /*!< The message of this object */
};

/*!
 * \brief Prints the message of an AddUserResult object to an ostream.
 * \param os The ostream to print to.
 * \param addUserResult The object to be printed.
 * \return A reference to 'os'.
 * \note Will print the same message that would be returned by
 *       addUserResult.getMessage()
 **/
std::ostream& operator<<(std::ostream& os, const AddUserResult& addUserResult);
} // namespace itsp3
#endif // INCG_ITSP3_ADD_USER_RESULT_HPP
