#include "check_password.hpp" // itsp3::check_password, ...
#include <doctest.h>

namespace {
constexpr char dummyUser[] = "Peter";
} // anonymous namespace

TEST_CASE("password_too_short_test")
{
  CHECK(
    itsp3::checkPassword(dummyUser, "")
    == itsp3::PasswordCheckingResult::TooShort);

  CHECK(
    itsp3::checkPassword(dummyUser, "1234567")
    == itsp3::PasswordCheckingResult::TooShort);

  CHECK(
    itsp3::checkPassword(dummyUser, "12345678")
    != itsp3::PasswordCheckingResult::TooShort);
}

TEST_CASE("password_too_few_lowercase_test")
{
  CHECK(
    itsp3::checkPassword(dummyUser, "ABCDEFG1234{")
    == itsp3::PasswordCheckingResult::TooFewLowerCaseCharacters);

  CHECK(
    itsp3::checkPassword(dummyUser, "aoeuoeuoeu,.u.pu,.u,.u,.17aa<<eeA ")
    != itsp3::PasswordCheckingResult::TooFewLowerCaseCharacters);
}

TEST_CASE("password_too_few_uppercase_test")
{
  CHECK(
    itsp3::checkPassword(dummyUser, "oeuaoeu[[{&&[&[{45545")
    == itsp3::PasswordCheckingResult::TooFewUpperCaseCharacters);

  CHECK(
    itsp3::checkPassword(dummyUser, "oeuaAAOEOEAOoeu[[{&&[&[{45545")
    != itsp3::PasswordCheckingResult::TooFewUpperCaseCharacters);
}

TEST_CASE("password_too_few_numbers_test")
{
  CHECK(
    itsp3::checkPassword(dummyUser, "oeuAAOEAOE[[[[[[[[[[")
    == itsp3::PasswordCheckingResult::TooFewNumbers);

  CHECK(
    itsp3::checkPassword(dummyUser, "oeuaoeu[[{&&[&[{45545")
    != itsp3::PasswordCheckingResult::TooFewNumbers);
}

TEST_CASE("password_too_few_special_characters_test")
{
  CHECK(
    itsp3::checkPassword(dummyUser, "o455AOEAOEAO45")
    == itsp3::PasswordCheckingResult::TooFewSpecialCharacters);

  CHECK(
    itsp3::checkPassword(dummyUser, "oeuaoeuA>[[{&&[&[{45545")
    != itsp3::PasswordCheckingResult::TooFewSpecialCharacters);
}

TEST_CASE("password_equal_to_username_test")
{
  CHECK(
    itsp3::checkPassword("PeterSchmidt123{}{{{{", "PeterSchmidt123{}{{{{")
    == itsp3::PasswordCheckingResult::EqualToUsername);

  CHECK(
    itsp3::checkPassword("Hannes", "Hannes1234oeuoeuOEAOE[{[{[{[{")
    != itsp3::PasswordCheckingResult::EqualToUsername);
}

TEST_CASE("password_ok_test")
{
  CHECK(
    itsp3::checkPassword("admin", "12eoaeOAEAEao[{{{{{{{(=}=222")
    == itsp3::PasswordCheckingResult::Ok);

  CHECK(
    itsp3::checkPassword("admin", "aA4{") != itsp3::PasswordCheckingResult::Ok);

  CHECK(
    itsp3::checkPassword("admin", "12345678AAAA{{{{{{{")
    != itsp3::PasswordCheckingResult::Ok);

  CHECK(
    itsp3::checkPassword("admin", "12345678{{{{aaaaaa{{{")
    != itsp3::PasswordCheckingResult::Ok);

  CHECK(
    itsp3::checkPassword("admin", "abcdefgAOEAEAOE{{{{{{")
    != itsp3::PasswordCheckingResult::Ok);

  CHECK(
    itsp3::checkPassword("admin", "12345678AAAAaaaa")
    != itsp3::PasswordCheckingResult::Ok);

  CHECK(
    itsp3::checkPassword("admin", "admin")
    != itsp3::PasswordCheckingResult::Ok);
}
