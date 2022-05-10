#include <gtest/gtest.h>

#include <libphp/dump_tokens.hpp>

#include <sstream>
#include <string>

TEST(LexerSuite, JustTest) {
  EXPECT_EQ(42 + 1, 43);
}

namespace php::test {

TEST(LexerSuite, ValidNumbers) {
  std::stringstream in("0 123456789");

  std::stringstream out;
  dump_tokens(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>\tValue '0'\n"
      "Loc=<1:2>\tValue '123456789'\n");
}

TEST(LexerSuite, ValidId) {
  std::stringstream in("a bNFDS fsddf");

  std::stringstream out;
  dump_tokens(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>\tId 'a'\n"
      "Loc=<1:2>\tId 'bNFDS'\n"
      "Loc=<1:8>\tId 'fsddf'\n");
}

TEST(LexerSuite, MathExpr) {
  std::stringstream in("(13 + 15 / 2) * 3 - 1 = 60.5");

  std::stringstream out;
  dump_tokens(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>\tL_Paren '('\n"
      "Loc=<1:1>\tValue '13'\n"
      "Loc=<1:4>\tPlus '+'\n"
      "Loc=<1:6>\tValue '15'\n"
      "Loc=<1:9>\tDefinition '/'\n"
      "Loc=<1:11>\tValue '2'\n"
      "Loc=<1:12>\tR_Paren ')'\n"
      "Loc=<1:14>\tMultiplication '*'\n"
      "Loc=<1:16>\tValue '3'\n"
      "Loc=<1:18>\tMinus '-'\n"
      "Loc=<1:20>\tValue '1'\n"
      "Loc=<1:22>\tEquality '='\n"
      "Loc=<1:24>\tValue '60'\n"
      "Loc=<1:26>\tPoint '.'\n"
      "Loc=<1:27>\tValue '5'\n");
}

}  // namespace php::test
