#include "binary_io.hpp" // itsp3::openFileForBinaryReading, itsp3::openFileForBinaryWriting
#include "record.hpp" // itsp3::Record
#include <climits>    // UCHAR_MAX
#include <cstdio>     // std::remove
#include <doctest.h>
#include <fstream> // std::ftream
#include <string>  // std::string

TEST_CASE("record_test")
{
  static constexpr char testFilePath[] = "./record_test.bin";
  const std::string     emptyString{};
  const std::string     largeString(UCHAR_MAX, ' ');
  const std::string     tooLargeString(UCHAR_MAX + 1U, ' ');

  const itsp3::Record record1{"Peter", "\xAB\xCD\xEF"};
  const itsp3::Record record2{"User", "\x12\x44"};

  std::fstream fs{};

  SUBCASE("empty_string_ok")
  {
    auto lambda = [&emptyString] {
      const itsp3::Record record{emptyString, emptyString};
    };
    CHECK_NOTHROW(lambda());
  }

  SUBCASE("large_string_ok")
  {
    auto lambda = [&largeString] {
      const itsp3::Record record{largeString, largeString};
    };
    CHECK_NOTHROW(lambda());
  }

  SUBCASE("too_large_string_throws")
  {
    auto lambda1 = [&tooLargeString, &emptyString] {
      const itsp3::Record record{tooLargeString, emptyString};
    };
    auto lambda2 = [&emptyString, &tooLargeString] {
      const itsp3::Record record{emptyString, tooLargeString};
    };
    CHECK_THROWS_AS(lambda1(), itsp3::TooLongStringForRecordException);
    CHECK_THROWS_AS(lambda2(), itsp3::TooLongStringForRecordException);
  }

  SUBCASE("read_write_test")
  {
    REQUIRE_UNARY(
      static_cast<bool>(itsp3::openFileForBinaryWriting(fs, testFilePath)));
    REQUIRE_UNARY(static_cast<bool>(record1.write(fs)));
    REQUIRE_UNARY(static_cast<bool>(record2.write(fs)));
    fs.close();
    REQUIRE_UNARY(static_cast<bool>(fs));

    REQUIRE_UNARY(
      static_cast<bool>(itsp3::openFileForBinaryReading(fs, testFilePath)));

    itsp3::Record record{};
    REQUIRE_UNARY(static_cast<bool>(itsp3::Record::read(fs, &record)));
    CHECK(record.getUsername() == record1.getUsername());
    CHECK(record.getHash() == record1.getHash());

    REQUIRE_UNARY(static_cast<bool>(itsp3::Record::read(fs, &record)));
    CHECK(record.getUsername() == record2.getUsername());
    CHECK(record.getHash() == record2.getHash());
    fs.close();
    REQUIRE_UNARY(static_cast<bool>(fs));

    REQUIRE(std::remove(testFilePath) == 0);
  }
}
