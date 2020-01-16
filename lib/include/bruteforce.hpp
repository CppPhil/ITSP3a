#ifndef INCG_ITSP3_BRUTEFORCE_HPP
#define INCG_ITSP3_BRUTEFORCE_HPP
#include <array>         // std::array
#include <cstddef>       // std::size_t
#include <pl/except.hpp> // PL_DEFINE_EXCEPTION_TYPE, PL_THROW_WITH_SOURCE_INFO
#include <stdexcept>     // std::logic_error
#include <string>        // std::string
#include <vector>        // std::vector

namespace itsp3 {
PL_DEFINE_EXCEPTION_TYPE(
  NoMatchInBruteforceAlgorithmException,
  std::logic_error);

/*!
 * \brief Bruteforce algorithm.
 * \param doesMatch Callable to determine if the current string matches.
 * \param alphabet The alphabet to use.
 * \throws NoMatchInBruteforceAlgorithmException
 * \note Can easily take a very long time to crack a password, depending on
 *       the length of the password and the length of the alphabet.
 *
 * Generates all the words of the alphabet 'alphabet' until a string is
 * generated for which doesMatch returns true.
 **/
template<std::size_t AlphabetSize, typename Callable>
std::string bruteforce(
  const Callable&                       doesMatch,
  const std::array<char, AlphabetSize>& alphabet)
{
  // iterate over the alphabet
  for (std::size_t curWordLen{0U}; curWordLen <= alphabet.size();
       ++curWordLen) {
    // will contain the current indices into the alphabet
    std::vector<std::size_t> indices(curWordLen, 0U);

    // will contain the current word generated
    std::string curWord(curWordLen, '\0');

  newIndices:

    // fill the current word with the characters from the alphabet
    // according to the current indices
    for (std::size_t i{0U}; i < curWordLen; ++i) {
      curWord[i] = alphabet[indices[i]];
    }

    // if it matches -> return the match.
    if (doesMatch(curWord)) {
      return curWord;
    }

    // iterate backwards over the indices.
    for (std::size_t i{curWordLen}; i-- > 0U;) {
      // advance the current index by 1 so the next character
      // will be selected.
      ++(indices[i]);

      // if it reached the end of the alphabet -> reset
      // and go increase the next index to the left.
      if (indices[i] == alphabet.size()) {
        indices[i] = 0U;
      }
      else {
        // if the current index didn't reach the end
        // create the new word from the new indices.
        goto newIndices;
      }
    }

    // if the above for loop exits and control flow reaches here
    // -> advance to the next word length.
  }

  // the algorithm should always find a match.
  PL_THROW_WITH_SOURCE_INFO(
    NoMatchInBruteforceAlgorithmException,
    "Bruteforce algorithm found no match");
  return "";
}
} // namespace itsp3
#endif // INCG_ITSP3_BRUTEFORCE_HPP
