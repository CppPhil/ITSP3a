/*!
 * \file binary_io.hpp
 * \brief Exports functions for binary I/O.
 **/
#ifndef INCG_ITSP3_BINARY_IO_HPP
#define INCG_ITSP3_BINARY_IO_HPP
#include <cstddef>       // std::size_t
#include <fstream>       // std::fstream
#include <iosfwd>        // std::ostream, std::istream
#include <pl/assert.hpp> // PL_DBG_CHECK_PRE
#include <string_view>   // std::string_view

namespace itsp3 {
/*!
 * \brief Opens the filestream 'fs' for binary reading from file at
 *        'pathToFile'.
 * \param fs The filestream to open for binary reading.
 * \param pathToFile The path to the file to be opened for binary reading.
 * \return A reference to 'fs'.
 * \warning Check whether opening the file succeeded using .operator bool()
 *          'fs' may not already be opened!
 **/
std::fstream& openFileForBinaryReading(
  std::fstream&    fs,
  std::string_view pathToFile);

/*!
 * \brief Opens the filestream 'fs' for binary writing to file at 'pathToFile'
 * \param fs The filestream to open for binary writing.
 * \param pathToFile The path to the file to be opened for binary writing.
 * \return A reference to 'fs'.
 * \note 'fs' will be opened in append mode, so that writing to it will
 *       append to the file by default.
 * \warning Check whether opening the file succeeded using .operator bool()
 *          'fs' may not already be opened!
 **/
std::fstream& openFileForBinaryWriting(
  std::fstream&    fs,
  std::string_view pathToFile);

/*!
 * \brief Write binary data to an ostream.
 * \param os The ostream to write binary data to.
 * \param data Pointer to the first (0th) byte of the data to write to 'os'.
 *             May not be nullptr or otherwise be invalid.
 * \param dataByteSize The size of the data pointed to by 'data' in bytes.
 *                     May not be incorrect!
 * \return A reference to 'os'.
 * \warning 'os' must've been opened in binary and in output mode!
 **/
std::ostream&
writeBinary(std::ostream& os, const void* data, std::size_t dataByteSize);

/*!
 * \brief Reads binary data from an istream.
 * \param is The istream to read binary data from.
 * \param data Pointer to the buffer to write data to.
 * \param dataByteSize The amount of bytes to read. May not be larger than
 *                     the byte size of the buffer pointed to by 'data'.
 * \return A reference to 'is'.
 **/
std::istream&
readBinary(std::istream& is, void* data, std::size_t dataByteSize);
} // namespace itsp3
#endif // INCG_ITSP3_BINARY_IO_HPP
