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

TEST(ParserSuite, IncorrectExample) {
  std::stringstream in(
      "<\?php\n"
      " $min = 10000\n"
      "\?>");

  std::stringstream out;
  get_ast_from_stream(in, out);

  EXPECT_EQ(out.str(), "3:0 missing ';' at '?'\n");
}

TEST(ParserSuite, MathExpr) {
  std::stringstream in(
      "<\?php\n"
      " $min = 12 + 32 / 2;\n"
      " $min++;\n"
      " $A = $min * 13;\n"
      "\?>");

  std::stringstream out;
  get_ast_from_stream(in, out);

  EXPECT_EQ(
      out.str(),
      "<?xml version=\"1.0\"?>\n"
      "<php>\n"
      "  <command>\n"
      "    <assign>$min = (12 + (32 / 2))</assign>\n"
      "  </command>\n"
      "  <command>($min++)</command>\n"
      "  <command>\n"
      "    <assign>$A = ($min * 13)</assign>\n"
      "  </command>\n"
      "</php>\n");
}

TEST(ParserSuite, IncorrectMathExpr) {
  std::stringstream in(
      "<\?php\n"
      "$min = 12 +- 13;\n"
      "$A = $min / 12;\n"
      "$B = $A */ 14;\n"
      "$C = $A$B;\n"
      "$D = $C 12;\n"
      "\?>");

  std::stringstream out;
  get_ast_from_stream(in, out);

  EXPECT_EQ(
      out.str(),
      "2:11 extraneous input '-' expecting {'fgets', '++', '--', '$', VALUE, "
      "STRING, '('}\n"
      "4:9 extraneous input '/' expecting {'fgets', '++', '--', '$', VALUE, "
      "STRING, '('}\n"
      "5:7 missing ';' at '$'\n"
      "6:8 extraneous input '12' expecting ';'\n");
}

TEST(ParserSuite, IfStatement) {
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

TEST(ParserSuite, CorrectIfStatement) {
  std::stringstream in(
      "<\?php\n"
      "if($numberA > $numberB * 12 - $numberA)\n"
      "{\n"
      "    $numberA++;\n"
      "}\n"
      "\?>\n");

  std::stringstream out;
  get_ast_from_stream(in, out);

  EXPECT_EQ(
      out.str(),
      "<?xml version=\"1.0\"?>\n"
      "<php>\n"
      "  <if>\n"
      "    <comparison>$numberA &gt; (($numberB * 12) - "
      "$numberA)</comparison>\n"
      "    <code_block>\n"
      "      <command>($numberA++)</command>\n"
      "    </code_block>\n"
      "  </if>\n"
      "</php>\n");
}

TEST(ParserSuite, IncorrectIfStatement) {
  std::stringstream in(
      "<\?php\n"
      "if($numberA >> $numberB * 12 - $numberA)\n"
      "{\n"
      "    $numberA++;\n"
      "}\n"
      "\?>\n");

  std::stringstream out;
  get_ast_from_stream(in, out);

  EXPECT_EQ(
      out.str(),
      "2:13 no viable alternative at input 'if($numberA>>'\n"
      "2:12 mismatched input '>' expecting ')'\n"
      "2:39 mismatched input ')' expecting ';'\n");
}

TEST(ParserSuite, IfElseStatement) {
  std::stringstream in(
      "<\?php\n"
      "$numberA = 15;\n"
      "$numberB = 21;\n"
      "if($numberA > $numberB)\n"
      "{\n"
      "    $numberB = $numberB + 8;\n"
      "}\n"
      "else\n"
      "{\n"
      "        $numberA = $numberA + $numberB;\n"
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
      "  <if_else_state>\n"
      "    <if>\n"
      "      <comparison>$numberA &gt; $numberB</comparison>\n"
      "      <code_block>\n"
      "        <command>\n"
      "          <assign>$numberB = ($numberB + 8)</assign>\n"
      "        </command>\n"
      "      </code_block>\n"
      "    </if>\n"
      "  </if_else_state>\n"
      "  <else>\n"
      "    <code_block>\n"
      "      <command>\n"
      "        <assign>$numberA = ($numberA + $numberB)</assign>\n"
      "      </command>\n"
      "    </code_block>\n"
      "  </else>\n"
      "</php>\n");
}

TEST(ParserSuite, WhileStatement) {
  std::stringstream in(
      "<\?php\n"
      "$i = 0;\n"
      "while($i < 8)\n"
      "{\n"
      "    $numberB = $numberB + 8;\n"
      "    $i++;\n"
      "}\n"
      "\?>");

  std::stringstream out;
  get_ast_from_stream(in, out);

  EXPECT_EQ(
      out.str(),
      "<\?xml version=\"1.0\"\?>\n"
      "<php>\n"
      "  <command>\n"
      "    <assign>$i = 0</assign>\n"
      "  </command>\n"
      "  <while>\n"
      "    <comparison>$i &lt; 8</comparison>\n"
      "    <code_block>\n"
      "      <command>\n"
      "        <assign>$numberB = ($numberB + 8)</assign>\n"
      "      </command>\n"
      "      <command>($i++)</command>\n"
      "    </code_block>\n"
      "  </while>\n"
      "</php>\n");
}

}  // namespace php::test