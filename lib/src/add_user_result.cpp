#include "add_user_result.hpp"
#include <ostream> // std::ostream
#include <string>  // std::string
#include <utility> // std:move

namespace itsp3 {
AddUserResult::AddUserResult(PasswordCheckingResult passwordCheckingResult)
  : m_ok{passwordCheckingResult == PasswordCheckingResult::Ok}
  , m_message{asString(passwordCheckingResult)}
{
}

AddUserResult::AddUserResult(Value ok, std::string message)
  : m_ok{ok == Value::Success}, m_message{std::move(message)}
{
}

AddUserResult::operator bool() const noexcept
{
  return m_ok;
}

std::string_view AddUserResult::getMessage() const noexcept
{
  return m_message;
}

std::ostream& operator<<(std::ostream& os, const AddUserResult& addUserResult)
{
  return os << addUserResult.getMessage();
}
} // namespace itsp3
