#include "string_scrubber.hpp"
#include <pl/zero_memory.hpp> // pl::secure_zero_memory

namespace itsp3 {
StringScrubber::StringScrubber(std::string& stringToScrub) noexcept
  : m_stringToScrub{&stringToScrub} // save a pointer to the std::string.
{
}

StringScrubber::~StringScrubber()
{
  // replace the memory currently owned by the string with 0x00 bytes
  pl::secure_zero_memory(&((*m_stringToScrub)[0U]), m_stringToScrub->size());
}
} // namespace itsp3
