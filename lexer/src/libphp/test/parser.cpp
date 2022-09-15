#include <gtest/gtest.h>

#include <libphp/parser.hpp>

#include <sstream>
#include <string>

TEST(ParserSuite, JustTest2) {
  EXPECT_EQ(42 + 1, 43);
}

namespace php::test {

void get_ast_from_stream(std::istream& in, std::ostream& out) {
  antlr4::ANTLRInputStream stream(in);
  PhpLexer lexer(&stream);
  auto parser_result = php::parse(lexer);
  if (!parser_result.errors_.empty()) {
    php::dump_errors(parser_result.errors_, out);
  } else {
    php::dump_ast(parser_result.document_, out);
  }
}

TEST(ParserSuite, SimleExample) {
  std::stringstream in(
      "<\?php\n"
      " $min = 10000;\n"
      " print(\"mmm, such crespy ass\");\n"
      "\?>");

  std::stringstream out;
  get_ast_from_stream(in, out);

  EXPECT_EQ(
      out.str(),
      "<\?xml version=\"1.0\"\?>\n"
      "<php>\n"
      "  <command>\n"
      "    < assign >10000</ assign >\n"
      "  </command>\n"
      "</php>\n");
}

}  // namespace php::test