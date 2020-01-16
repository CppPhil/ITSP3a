#ifndef INCG_ITSP3_PRINT_BYTES_AS_ASCII_HPP
#define INCG_ITSP3_PRINT_BYTES_AS_ASCII_HPP
#include <cstddef> // std::size_t
#include <iosfwd>  // std::ostream

namespace itsp3 {
/*!
 * \brief Type to print memory as ASCII characters.
 **/
class PrintBytesAsAscii {
public:
  using this_type = PrintBytesAsAscii;

  /*!
   * \brief Creates a PrintBytesAsAscii object.
   * \param data Pointer to the beginning of the region of memory
   *             to be printed as ASCII characters.
   *             May not be nullptr or otherwise be invalid!
   * \param dataByteSize The size of the region of memory pointed to by
   *                     data. May not be incorrect!
   **/
  PrintBytesAsAscii(const void* data, std::size_t dataByteSize) noexcept;

  /*!
   * \brief Prints the memory that the PrintBytesAsAscii object given
   *        references as ASCII characters.
   * \param os The ostream to print to.
   * \param pbaa The PrintBytesAsAscii object that references some region
   *             of memory that shall be printed as ASCII characters.
   * \return A reference to 'os'.
   **/
  friend std::ostream& operator<<(
    std::ostream&            os,
    const PrintBytesAsAscii& pbaa);

private:
  const void* m_data;
  std::size_t m_dataByteSize;
};
} // namespace itsp3
#endif // INCG_ITSP3_PRINT_BYTES_AS_ASCII_HPP
