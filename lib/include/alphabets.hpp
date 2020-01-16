/*!
 * \file alphabets.hpp
 * \brief Exports utilities for creating alphabets as std::arrays from
 *        ranges of ASCII values.
 **/
#ifndef INCG_ITSP3_ALPHABETS_HPP
#define INCG_ITSP3_ALPHABETS_HPP
#include <array>                  // std::array
#include <pl/cont/make_array.hpp> // pl::cont::makeArray
#include <type_traits> // std::index_sequence, std::make_index_sequence

namespace itsp3 {
namespace detail {
/*!
 * \brief Implementation function of makeAlphabet.
 * \note Not to be used directly.
 **/
template<int From, int To, std::size_t... Indices>
constexpr std::array<char, To - From> makeAlphabetImpl(
  std::index_sequence<Indices...>)
{
  /*  If 'From' is 0x41 (The ASCII value for 'A')
   *  and 'To' is 0x43  (The ASCII value for 'C')
   *  then sizeof...(Indices) will be 2.
   *  So there will be 2 std::size_ts in the non-type
   *  template parameter pack, since 0x43 - 0x41 = 2.
   *  Then the statement below will 'expand' to:
   *  { { 0x41 + 0, 0x41 + 1 } }
   *  resulting in:
   *  { { 0x41, 0x42 } }
   *  which creates a
   *  std::array<char, 2>{ 'A', 'B' }
   *  at compile time.
   */
  return {{(From + static_cast<int>(Indices))...}};
}
} // namespace detail

/*!
 * \brief Compile time function to create an alphabet.
 * \return The alphabet created.
 * \warning Assumes that the underlying C++ implementation implements
 *          the char type using ASCII encoding, which is very likely in
 *practice, albeit specifically not required by the C++ standard.
 *
 * Creates an alphabet as std::array at compile time.
 * 'From' indicates the ASCII value at which the alphabet shall begin.
 * 'To' indicates the ASCII value at which the alphabet shall end.
 * Note that the character with the ASCII value of 'To' will not be included
 * in the resulting std::array, as the range denoted by ['From' .. 'To') is
 * half open, much like C++ style iterators.
 **/
template<int From, int To>
constexpr std::array<char, To - From> makeAlphabet()
{
  static_assert(To >= From, "To was less than From!");

  // The index_sequence is effectively a compile time (type based) list
  // of compile time std::size_t objects.
  // An index_sequence<5> would 'hold' the values 0U, 1U, 2U, 3U, 4U
  // in its type.
  // The index_sequence object created (at compile time) is merely used
  // so that the implementation function can deduce the std::size_ts
  // as a template non-type parameter pack, which can then be used
  // in a template parameter pack expansion context.
  return detail::makeAlphabetImpl<From, To>(
    std::make_index_sequence<To - From>{});
}
namespace {
/*!
 * The ASCII alphabet.
 * Contains the characters of the range [0x00 .. 0x80), which is equivalent to
 * [0x00 .. 0x7F].
 * See an ASCII chart here: http://en.cppreference.com/w/cpp/language/ascii
 **/
constexpr std::array<char, 0x80 - 0x00> asciiAlphabet
  = makeAlphabet<0x00, 0x80>();
} // anonymous namespace
} // namespace itsp3
#endif // INCG_ITSP3_ALPHABETS_HPP
