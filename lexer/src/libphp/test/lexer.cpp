#include <gtest/gtest.h>

#include <libphp/dump_tokens.hpp>

#include <sstream>
#include <string>

namespace php::test {

void dump_tokens_in(std::istream& in, std::ostream& out) {
  antlr4::ANTLRInputStream stream(in);
  PhpLexer lexer(&stream);
  dump_tokens(lexer, out);
}

TEST(LexerSuite, JustTest) {
  EXPECT_EQ(42 + 1, 43);
}

TEST(LexerSuite, ValidNumbers) {
  std::stringstream in("0 123456789");

  std::stringstream out;
  dump_tokens_in(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>\tVALUE '0'\n"
      "Loc=<1:2>\tVALUE '123456789'\n");
}

TEST(LexerSuite, ValidId) {
  std::stringstream in("a bNFDS fsddf");

  std::stringstream out;
  dump_tokens_in(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>\tID 'a'\n"
      "Loc=<1:2>\tID 'bNFDS'\n"
      "Loc=<1:8>\tID 'fsddf'\n");
}

TEST(LexerSuite, MathExpr) {
  std::stringstream in("(13 + 15 / 2) * 3 - 1 = 60.5");

  std::stringstream out;
  dump_tokens_in(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>\tLP '('\n"
      "Loc=<1:1>\tVALUE '13'\n"
      "Loc=<1:4>\tPLUS '+'\n"
      "Loc=<1:6>\tVALUE '15'\n"
      "Loc=<1:9>\tDEF '/'\n"
      "Loc=<1:11>\tVALUE '2'\n"
      "Loc=<1:12>\tRP ')'\n"
      "Loc=<1:14>\tMUL '*'\n"
      "Loc=<1:16>\tVALUE '3'\n"
      "Loc=<1:18>\tMINUS '-'\n"
      "Loc=<1:20>\tVALUE '1'\n"
      "Loc=<1:22>\tASSIGN '='\n"
      "Loc=<1:24>\tVALUE '60'\n"
      "Loc=<1:26>\tPOINT '.'\n"
      "Loc=<1:27>\tVALUE '5'\n");
}

TEST(LexerSuite, Array) {
  std::stringstream in(
      "<?php\n"
      "$arr = array(5, 3, 6, 1, 2, 3, 4);\n"
      "?>");

  std::stringstream out;
  dump_tokens_in(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>	SBL '<'\n"
      "Loc=<1:1>	QM '?'\n"
      "Loc=<1:2>	PHP 'php'\n"
      "Loc=<2:0>	DOLL '$'\n"
      "Loc=<2:1>	ID 'arr'\n"
      "Loc=<2:5>	ASSIGN '='\n"
      "Loc=<2:7>	ARRAY 'array'\n"
      "Loc=<2:12>	LP '('\n"
      "Loc=<2:13>	VALUE '5'\n"
      "Loc=<2:14>	COMMA ','\n"
      "Loc=<2:16>	VALUE '3'\n"
      "Loc=<2:17>	COMMA ','\n"
      "Loc=<2:19>	VALUE '6'\n"
      "Loc=<2:20>	COMMA ','\n"
      "Loc=<2:22>	VALUE '1'\n"
      "Loc=<2:23>	COMMA ','\n"
      "Loc=<2:25>	VALUE '2'\n"
      "Loc=<2:26>	COMMA ','\n"
      "Loc=<2:28>	VALUE '3'\n"
      "Loc=<2:29>	COMMA ','\n"
      "Loc=<2:31>	VALUE '4'\n"
      "Loc=<2:32>	RP ')'\n"
      "Loc=<2:33>	SEMI ';'\n"
      "Loc=<3:0>	QM '?'\n"
      "Loc=<3:1>	SBR '>'\n");
}

TEST(LexerSuite, While) {
  std::stringstream in(
      "while ($i < 2) {\n"
      "}");

  std::stringstream out;
  dump_tokens_in(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>	WHILE 'while'\n"
      "Loc=<1:6>	LP '('\n"
      "Loc=<1:7>	DOLL '$'\n"
      "Loc=<1:8>	ID 'i'\n"
      "Loc=<1:10>	SBL '<'\n"
      "Loc=<1:12>	VALUE '2'\n"
      "Loc=<1:13>	RP ')'\n"
      "Loc=<1:15>	LB '{'\n"
      "Loc=<2:0>	RB '}'\n");
}

TEST(LexerSuite, If) {
  std::stringstream in(
      "if ($numberA % $i == 0 && $numberB % $i == 0) {\n"
      "    $nod = $i;\n"
      "    break;\n"
      "}");

  std::stringstream out;
  dump_tokens_in(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>	IF 'if'\n"
      "Loc=<1:3>	LP '('\n"
      "Loc=<1:4>	DOLL '$'\n"
      "Loc=<1:5>\tID 'numberA'\n"
      "Loc=<1:13>	MOD '%'\n"
      "Loc=<1:15>	DOLL '$'\n"
      "Loc=<1:16>	ID 'i'\n"
      "Loc=<1:18>	EQ '=='\n"
      "Loc=<1:21>	VALUE '0'\n"
      "Loc=<1:23>	AND '&&'\n"
      "Loc=<1:26>	DOLL '$'\n"
      "Loc=<1:27>	ID 'numberB'\n"
      "Loc=<1:35>	MOD '%'\n"
      "Loc=<1:37>	DOLL '$'\n"
      "Loc=<1:38>	ID 'i'\n"
      "Loc=<1:40>	EQ '=='\n"
      "Loc=<1:43>	VALUE '0'\n"
      "Loc=<1:44>	RP ')'\n"
      "Loc=<1:46>	LB '{'\n"
      "Loc=<2:4>	DOLL '$'\n"
      "Loc=<2:5>	ID 'nod'\n"
      "Loc=<2:9>	ASSIGN '='\n"
      "Loc=<2:11>	DOLL '$'\n"
      "Loc=<2:12>	ID 'i'\n"
      "Loc=<2:13>	SEMI ';'\n"
      "Loc=<3:4>	BREAK 'break'\n"
      "Loc=<3:9>	SEMI ';'\n"
      "Loc=<4:0>	RB '}'\n");
}

TEST(LexerSuite, Echo) {
  std::stringstream in("echo \" наименьшое число \" . $min;");

  std::stringstream out;
  dump_tokens_in(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>	ECHO 'echo'\n"
      "Loc=<1:5>	STRING '\" наименьшое число \"'\n"
      "Loc=<1:26>	POINT '.'\n"
      "Loc=<1:28>	DOLL '$'\n"
      "Loc=<1:29>	ID 'min'\n"
      "Loc=<1:32>	SEMI ';'\n");
}

}  // namespace php::test