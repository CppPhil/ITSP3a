#ifndef INCG_ITSP3_STRING_SCRUBBER_HPP
#define INCG_ITSP3_STRING_SCRUBBER_HPP
#include <string> // std::string

namespace itsp3 {
/*!
 * \brief Type to replace a strings memory with 0x00 bytes on scope exit.
 **/
class StringScrubber {
public:
  using this_type = StringScrubber;

  /*!
   * \brief Creates a StringScrubber object.
   * \param stringToScrub reference to the string to have its memory scrubbed
   *                      in the destructor.
   **/
  explicit StringScrubber(std::string& stringToScrub) noexcept;

  /*!
   * \brief Safely replaces the memory that the string passed into the
   *        constructor owns with 0x00 bytes.
   **/
  ~StringScrubber();

private:
  std::string* m_stringToScrub; /*!< Pointer to the string
                                 *   passed into the ctor
                                 **/
};
} // namespace itsp3
#endif // INCG_ITSP3_STRING_SCRUBBER_HPP
