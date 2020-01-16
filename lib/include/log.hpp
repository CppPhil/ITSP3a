/*!
 * \file log.hpp
 * \brief Exports the ITSP3_LOG macro that shall be used to write debug
 *        log entries to the debug.log file.
 *        Only the ITSP3_LOG macro is supposed to be used from this file
 *        all the other symbols exported are considered to be implementation
 *        details.
 **/
#ifndef INCG_ITSP3_LOG_HPP
#define INCG_ITSP3_LOG_HPP
#include <fstream>                 // std::ofstream
#include <pl/current_function.hpp> // PL_CURRENT_FUNCTION
#include <pl/source_line.hpp>      // PL_SOURCE_LINE
#include <string>                  // std::string

/*!
 * \def ITSP3_LOG
 * \brief Macro to write to the debug log of the application.
 * \note Does nothing in release mode.
 * \warning May only be used within a function.
 *          Not thread safe.
 **/

#define ITSP3_LOG \
  ::itsp3::detail::createLogEntry(__FILE__, PL_SOURCE_LINE, PL_CURRENT_FUNCTION)

namespace itsp3 {
namespace detail {
class Log {
public:
  /*!
   * \brief Fetches the singleton object.
   * \return A reference the global Log singleton object.
   **/
  static Log& getInstance();

  /*!
   * \brief Prints a printable object to the Log singleton.
   * \param ty The object to be printed to the Log.
   * \return A reference to the Log.
   * \note Will only print anything in debug mode.
   **/
  template<typename Ty>
  Log& operator<<(const Ty& ty)
  {
#ifdef DEBUG_MODE
    m_ofstream << ty;
#endif // DEBUG_MODE
    return *this;
  }

private:
  /*!
   * \brief Default constructs the Log singleton, not associated with any
   *        file.
   * \note Used in release mode.
   **/
  Log();

  /*!
   * \brief Constructs the Log singleton.
   * \param logFilePath Path to the file to write the debug log to.
   * \note Used in debug mode.
   **/
  explicit Log(std::string logFilePath);

  std::string   m_logFilePath; /*!< Path to the debug.log file */
  std::ofstream m_ofstream;    /*!< The filestream */
};

/*!
 * \brief Implementation function used by the ITSP_LOG macro.
 *        Used to create a new Log entry.
 * \param file A null-terminated byte character string that represents the
 *             current file. May not be nullptr or otherwise be invalid!
 * \param line A null-terminated byte character string that represents the
 *             current source line. May not be nullptr or otherwise be invalid!
 * \param function A null-terminated byte character string that represents the
 *                 current function. May not be nullptr or otherwise be invalid!
 * \return A reference to the Log singleton.
 **/
Log& createLogEntry(const char* file, const char* line, const char* function);
} // namespace detail
} // namespace itsp3
#endif // INCG_ITSP3_LOG_HPP
