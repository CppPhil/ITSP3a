#include "log.hpp"
#include <cstdint> // std::uint64_t
#include <utility> // std::move

namespace itsp3 {
namespace detail {
Log& Log::getInstance()
{
#ifdef DEBUG_MODE
  static Log log{
    "./debug.log" // The path to the debug.log file.
  };
#else
  static Log log{};
#endif
  return log;
}

Log::Log()
  : m_logFilePath{}
  , m_ofstream{} // not associated with any file in release mode.
{
}

Log::Log(std::string logFilePath)
  : m_logFilePath{std::move(logFilePath)}, m_ofstream{m_logFilePath}
{
}

Log& createLogEntry(const char* file, const char* line, const char* function)
{
  static std::uint64_t entryNumber{0U};

  Log& log{Log::getInstance()};

  ++entryNumber;

  log << "\n\n"
      << "Entry:    " << entryNumber << '\n'
      << "File:     " << file << '\n'
      << "Line:     " << line << '\n'
      << "Function: " << function << '\n'
      << "Message:  ";

  return log;
}
} // namespace detail
} // namespace itsp3
