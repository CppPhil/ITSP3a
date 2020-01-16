#include "print_bytes_as_ascii.hpp"
#include <ostream> // std::ostream

namespace itsp3 {
PrintBytesAsAscii::PrintBytesAsAscii(
  const void* data,
  std::size_t dataByteSize) noexcept
  : m_data{data}, m_dataByteSize{dataByteSize}
{
}

std::ostream& operator<<(std::ostream& os, const PrintBytesAsAscii& pbaa)
{
  // interpret the memory as 'char'
  const char* const p{static_cast<const char*>(pbaa.m_data)};
  const std::size_t siz{pbaa.m_dataByteSize};

  // Treating the pointer as an 'array' seems to be
  // easier to optimize for the compiler, rather than
  // using pointers as 'iterators'.
  for (std::size_t i{0U}; i < siz; ++i) {
    os << p[i];
  }

  return os;
}
} // namespace itsp3
