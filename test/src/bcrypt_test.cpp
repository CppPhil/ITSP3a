#include "bcrypt.hpp" // itsp3::Bcrypt
#include <cassert>    // assert
#include <ciso646>    // and
#include <cstddef>    // std::size_t
#include <cstdio>     // std::remove
#include <doctest.h>
#include <iterator>                      // std::begin
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::copy
#include <string> // std::string, std::literals::string_literals::operator""s
#include <unordered_map> // std::unordered_map

TEST_CASE("bcrypt_test")
{
  using namespace std::literals::string_literals;

  // the file to write to and read from for the test
  // note that the subcases should remember to delete the file.
  static constexpr char testBinFile[] = "./test_data.bin";

  // maximum username / password length still acceptable
  static const std::size_t maxSize = BCRYPT_HASHSIZE;

  // too long username / password length
  static const std::size_t tooLarge = maxSize + 1U;

  static const std::string largestAcceptablePassword{[] {
    static const std::string beginning{"bA1{"};
    std::string              retVal(maxSize, ' ');

    assert((beginning.size() <= maxSize) and "Severe logic error");

    pl::algo::copy(beginning, std::begin(retVal));

    return retVal;
  }()};

  // the default records to fill the test file with
  static const std::unordered_map<std::string, std::string> records{
    {"Peter"s, "passwordA1{"s},
    {"Hannes"s, "geheimA1{"s},
    {"Uwe"s, "ABCDIEKATZELAUEFTIMSCHNEEa1{"s},
    {"testuser"s, "aaatestA1{"s},
    {"root"s, "uoeaoooeA1{"s},
    {"defaultuser"s, "letmeinA1{"s},
    {"admin"s, "123456aA{"s},
    {std::string(maxSize, ' '), "pwbA1{4555565555"s},
    {"user"s, largestAcceptablePassword}};

  itsp3::Bcrypt bcrypt{testBinFile};

  // fill the file with the default test records
  for (const auto& p : records) {
    const std::string& username{p.first};
    const std::string& password{p.second};

    REQUIRE_UNARY(bcrypt.addUser(username, password));
  }

  SUBCASE("can_add_new_users")
  {
    CHECK_UNARY(bcrypt.addUser("peter", "passwordbA1{"));
    CHECK_UNARY(bcrypt.addUser("Franz", "meinpasswortbA1{"));

    REQUIRE(std::remove(testBinFile) == 0);
  }

  SUBCASE("can_not_add_existing_users")
  {
    CHECK_UNARY_FALSE(bcrypt.addUser("Peter", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.addUser("Hannes", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.addUser("Uwe", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.addUser("testuser", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.addUser("root", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.addUser("defaultuser", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.addUser("admin", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.addUser(std::string(maxSize, ' '), "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.addUser("user", "dummybA1{"));

    REQUIRE(std::remove(testBinFile) == 0);
  }

  SUBCASE("can_not_add_users_with_too_long_username")
  {
    CHECK_UNARY_FALSE(bcrypt.addUser(std::string(tooLarge, 'a'), "pwbA1{"));

    REQUIRE(std::remove(testBinFile) == 0);
  }

  SUBCASE("can_not_add_users_with_too_long_password")
  {
    CHECK_UNARY_FALSE(bcrypt.addUser("ok", largestAcceptablePassword + "a"));

    REQUIRE(std::remove(testBinFile) == 0);
  }

  SUBCASE("can_not_add_same_user_twice")
  {
    CHECK_UNARY(bcrypt.addUser("testusername", "aeoaoeaeaepwbA1{"));
    CHECK_UNARY_FALSE(bcrypt.addUser("testusername", "?aaaaaaa??bA1{"));

    REQUIRE(std::remove(testBinFile) == 0);
  }

  SUBCASE("correct_passwords_are_accepted")
  {
    for (const auto& p : records) {
      const std::string& username{p.first};
      const std::string& password{p.second};

      CHECK_UNARY(bcrypt.checkPasswordValidity(username, password));
    }

    REQUIRE(std::remove(testBinFile) == 0);
  }

  SUBCASE("incorrect_passwords_are_not_accepted")
  {
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("Peter", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("Hannes", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("Uwe", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("testuser", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("root", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("defaultuser", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("admin", "dummybA1{"));
    CHECK_UNARY_FALSE(
      bcrypt.checkPasswordValidity(std::string(maxSize, ' '), "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("user", "dummybA1{"));
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("Peter", "password bA1{"));

    REQUIRE(std::remove(testBinFile) == 0);
  }

  SUBCASE("passwords_for_non_existent_users_are_not_accepted")
  {
    CHECK_UNARY_FALSE(bcrypt.checkPasswordValidity("???", "pwbA1{"));
    CHECK_UNARY_FALSE(
      bcrypt.checkPasswordValidity("!!!", "ABCDIEKATZELAUEFTIMSCHNEEbA1{"));

    REQUIRE(std::remove(testBinFile) == 0);
  }
}
