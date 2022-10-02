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
      " print(\"Hello, world!\");\n"
      "\?>");

  std::stringstream out;
  get_ast_from_stream(in, out);

  EXPECT_EQ(
      out.str(),
      "<\?xml version=\"1.0\"\?>\n"
      "<php>\n"
      "  <command>\n"
      "    <assign>$min = 10000</assign>\n"
      "  </command>\n"
      "  <command>\n"
      "    <print>\"Hello, world!\"</print>\n"
      "  </command>\n"
      "</php>\n");
}

TEST(ParserSuite, IfState) {
  std::stringstream in(
      "<\?php\n"
      "$numberA = 15;\n"
      "$numberB = 21;\n"
      "if($numberA > $numberB)\n"
      "{\n"
      "    $numberB = $numberB + 8;\n"
      "}\n"
      "\?>\n");

  std::stringstream out;
  get_ast_from_stream(in, out);

  EXPECT_EQ(
      out.str(),
      "<?xml version=\"1.0\"?>\n"
      "<php>\n"
      "  <command>\n"
      "    <assign>$numberA = 15</assign>\n"
      "  </command>\n"
      "  <command>\n"
      "    <assign>$numberB = 21</assign>\n"
      "  </command>\n"
      "  <if>\n"
      "    <comparison>$numberA &gt; $numberB</comparison>\n"
      "    <code_block>\n"
      "      <command>\n"
      "        <assign>$numberB = ($numberB + 8)</assign>\n"
      "      </command>\n"
      "    </code_block>\n"
      "  </if>\n"
      "</php>\n");
}

}  // namespace php::test