#include <gtest/gtest.h>

#include <libphp/dump_tokens.hpp>

#include <sstream>
#include <string>

TEST(LexerSuite, JustTest) {
  EXPECT_EQ(42 + 1, 43);
}

namespace php::test {

TEST(LexerSuite, ValidNumbers) {
  // Given
  std::stringstream in("0 123456789");

  // When
  std::stringstream out;
  dump_tokens(in, out);

  // Then
  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>\tValue '0'\n"
      "Loc=<1:2>\tValue '123456789'\n");
}

TEST(LexerSuite, ValidId) {
  // Given
  std::stringstream in("a bNFDS fsddf");

  // When
  std::stringstream out;
  dump_tokens(in, out);

  // Then
  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>\tId 'a'\n"
      "Loc=<1:2>\tId 'bNFDS'\n"
      "Loc=<1:8>\tId 'fsddf'\n");
}

}  // namespace php::test
