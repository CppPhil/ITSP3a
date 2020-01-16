#include "../include/add_user_result.hpp"
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <string> // std::string
#include <ostream> // std::ostream
#include <utility> // std:move

namespace itsp3
{
AddUserResult::AddUserResult(
    PasswordCheckingResult passwordCheckingResult)
    : m_ok{ passwordCheckingResult == PasswordCheckingResult::Ok },
      m_message{ boost::lexical_cast<std::string>(passwordCheckingResult) }
{
}

AddUserResult::AddUserResult(Value ok, std::string message)
    : m_ok{ ok == Value::Success },
      m_message{ std::move(message) }
{
}

AddUserResult::operator bool() const noexcept
{
    return m_ok;
}

boost::string_ref AddUserResult::getMessage() const noexcept
{
    return m_message;
}

std::ostream &operator<<(
    std::ostream &os,
    const AddUserResult &addUserResult)
{
    return os << addUserResult.getMessage();
}
} // namespace itsp3

