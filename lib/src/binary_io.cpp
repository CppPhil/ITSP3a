#include "binary_io.hpp"
#include "log.hpp"                   // ITSP3_LOG
#include "print_bytes_as_ascii.hpp"  // itsp3::PrintBytesAsAscii
#include <ciso646>                   // not
#include <ostream>                   // std::ostream
#include <pl/print_bytes_as_hex.hpp> // pl::print_bytes_as_hex

namespace itsp3 {
std::fstream& openFileForBinaryReading(
  std::fstream&    fs,
  std::string_view pathToFile)
{
  static constexpr auto flags = std::ios_base::in | std::ios_base::binary;

  PL_DBG_CHECK_PRE(not fs.is_open());
  fs.open(pathToFile.data(), flags);
  return fs;
}

std::fstream& openFileForBinaryWriting(
  std::fstream&    fs,
  std::string_view pathToFile)
{
  static constexpr auto flags // use app flag to append rather than overwrite
    = std::ios_base::out | std::ios_base::app | std::ios_base::binary;

  PL_DBG_CHECK_PRE(not fs.is_open());
  fs.open(pathToFile.data(), flags);
  return fs;
}

std::ostream&
writeBinary(std::ostream& os, const void* data, std::size_t dataByteSize)
{
  ITSP3_LOG << "Writing data:\n"
            << "hex:   " << pl::print_bytes_as_hex{data, dataByteSize} << '\n'
            << "ASCII: " << PrintBytesAsAscii{data, dataByteSize};

  return os.write(
    static_cast<const char*>(data), static_cast<std::streamsize>(dataByteSize));
}

std::istream& readBinary(std::istream& is, void* data, std::size_t dataByteSize)
{
  return is.read(
    static_cast<char*>(data), static_cast<std::streamsize>(dataByteSize));
}
} // namespace itsp3
