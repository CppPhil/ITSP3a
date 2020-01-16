#ifndef INCG_ITSP3_RECORD_HPP
#define INCG_ITSP3_RECORD_HPP
#include <iosfwd>        // std::ostream, std::istream
#include <pl/except.hpp> // PL_THROW_WITH_SOURCE_INFO, PL_DEFINE_EXCEPTION_TYPE
#include <stdexcept>     // std::logic_error
#include <string>        // std::string
#include <string_view>   // std::string_view

namespace itsp3 {
PL_DEFINE_EXCEPTION_TYPE(TooLongStringForRecordException, std::logic_error);
/*!
 * \brief Type that represents a record of a username and the associated hash
 *        in the binary file.
 **/
class Record {
public:
  using this_type = Record;

  /*!
   * \brief Creates a Record by reading from an inputstream.
   * \param is The input stream to read from.
   * \param outParam Pointer to the record object to write to.
   *                 May not be nullptr or otherwise be invalid!
   * \return A reference to 'is'.
   * \warning 'is' must be opened and have been opened with the binary flag.
   *          Check the state of the istream after calling this function!
   **/
  static std::istream& read(std::istream& is, Record* outParam);

  /*!
   * \brief Default constructs a Record leaving both data members default
   *        constructed (empty strings).
   **/
  Record() noexcept;

  /*!
   * \brief Creates a Record object.
   * \param username The username to use.
   * \param hash The hash to use.
   **/
  Record(std::string username, std::string hash);

  /*!
   * \brief Writes this record to 'os'.
   * \param os The ostream to write to.
   * \return A reference to 'os'.
   * \warning 'os' must be opened and have been opened in binary mode.
   *          Check the state of the ostream after calling this function!
   **/
  std::ostream& write(std::ostream& os) const;

  /*!
   * \brief Read accessor for the username.
   * \return A std::string_view to the username.
   **/
  std::string_view getUsername() const noexcept;

  /*!
   * \brief Read accessor for the hash.
   * \return A std::string_view to the hash.
   **/
  std::string_view getHash() const noexcept;

private:
  std::string m_username;
  std::string m_hash;
};
} // namespace itsp3
#endif // INCG_ITSP3_RECORD_HPP
