#include "alphabets.hpp"  // itsp3::asciiAlphabet
#include "bruteforce.hpp" // itsp3::bruteforce
#include <doctest.h>      // TEST_CASE, CHECK
#include <string>         // std::string
#include <string_view>    // std::string_view
#include <utility>        // std::move

TEST_CASE("bruteforce_test")
{
  // a lambda that take a password and returns a lambda, which will
  // accept a string, returning true if that string matches the password.
  auto makePasswordChecker = [](std::string password) {
    return [pw = std::move(password)](std::string_view input) {
      return pw == input;
    };
  };

  CHECK(itsp3::bruteforce(makePasswordChecker(""), itsp3::asciiAlphabet) == "");

  CHECK(
    itsp3::bruteforce(makePasswordChecker("a"), itsp3::asciiAlphabet) == "a");

  CHECK(
    itsp3::bruteforce(makePasswordChecker("ab"), itsp3::asciiAlphabet) == "ab");

  CHECK(
    itsp3::bruteforce(makePasswordChecker("abc"), itsp3::asciiAlphabet)
    == "abc");
}
