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

TEST(LexerSuite, Foreach) {
  std::stringstream in(
      "foreach ($arr as &$value) {\n"
      "    if ($min > $value) :\n"
      "        $min = $value;\n"
      "    endif;\n"
      "}");

  std::stringstream out;
  dump_tokens(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>	Foreach 'foreach'\n"
      "Loc=<1:8>	L_Paren '('\n"
      "Loc=<1:9>	Dollar '$'\n"
      "Loc=<1:10>	Id 'arr'\n"
      "Loc=<1:14>	As 'as'\n"
      "Loc=<1:17>	Link '&'\n"
      "Loc=<1:18>	Dollar '$'\n"
      "Loc=<1:19>	Id 'value'\n"
      "Loc=<1:24>	R_Paren ')'\n"
      "Loc=<1:26>	L_Brace '{'\n"
      "Loc=<2:4>	If 'if'\n"
      "Loc=<2:7>	L_Paren '('\n"
      "Loc=<2:8>	Dollar '$'\n"
      "Loc=<2:9>	Id 'min'\n"
      "Loc=<2:13>	Sharp_Brackets_Right '>'\n"
      "Loc=<2:15>	Dollar '$'\n"
      "Loc=<2:16>	Id 'value'\n"
      "Loc=<2:21>	R_Paren ')'\n"
      "Loc=<2:23>	Colon ':'\n"
      "Loc=<3:8>	Dollar '$'\n"
      "Loc=<3:9>	Id 'min'\n"
      "Loc=<3:13>	Equality '='\n"
      "Loc=<3:15>	Dollar '$'\n"
      "Loc=<3:16>	Id 'value'\n"
      "Loc=<3:21>	Semicolon ';'\n"
      "Loc=<4:4>	Endif 'endif'\n"
      "Loc=<4:9>	Semicolon ';'\n"
      "Loc=<5:0>	R_Brace '}'\n");
}

TEST(LexerSuite, Array) {
  std::stringstream in(
      "<?php\n"
      "$arr = array(5, 3, 6, 1, 2, 3, 4);\n"
      "?>");

  std::stringstream out;
  dump_tokens(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>	Sharp_Brackets_Left '<'\n"
      "Loc=<1:1>	Question_Mark '?'\n"
      "Loc=<1:2>	Php 'php'\n"
      "Loc=<2:0>	Dollar '$'\n"
      "Loc=<2:1>	Id 'arr'\n"
      "Loc=<2:5>	Equality '='\n"
      "Loc=<2:7>	Array 'array'\n"
      "Loc=<2:12>	L_Paren '('\n"
      "Loc=<2:13>	Value '5'\n"
      "Loc=<2:14>	Coma ','\n"
      "Loc=<2:16>	Value '3'\n"
      "Loc=<2:17>	Coma ','\n"
      "Loc=<2:19>	Value '6'\n"
      "Loc=<2:20>	Coma ','\n"
      "Loc=<2:22>	Value '1'\n"
      "Loc=<2:23>	Coma ','\n"
      "Loc=<2:25>	Value '2'\n"
      "Loc=<2:26>	Coma ','\n"
      "Loc=<2:28>	Value '3'\n"
      "Loc=<2:29>	Coma ','\n"
      "Loc=<2:31>	Value '4'\n"
      "Loc=<2:32>	R_Paren ')'\n"
      "Loc=<2:33>	Semicolon ';'\n"
      "Loc=<3:0>	Question_Mark '?'\n"
      "Loc=<3:1>	Sharp_Brackets_Right '>'\n");
}

TEST(LexerSuite, For) {
  std::stringstream in(
      "for ($i = 2;; ++$i) {\n"
      "}");

  std::stringstream out;
  dump_tokens(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>	For 'for'\n"
      "Loc=<1:4>	L_Paren '('\n"
      "Loc=<1:5>	Dollar '$'\n"
      "Loc=<1:6>	Id 'i'\n"
      "Loc=<1:8>	Equality '='\n"
      "Loc=<1:10>	Value '2'\n"
      "Loc=<1:11>	Semicolon ';'\n"
      "Loc=<1:12>	Semicolon ';'\n"
      "Loc=<1:14>	Increment '++'\n"
      "Loc=<1:16>	Dollar '$'\n"
      "Loc=<1:17>	Id 'i'\n"
      "Loc=<1:18>	R_Paren ')'\n"
      "Loc=<1:20>	L_Brace '{'\n"
      "Loc=<2:0>	R_Brace '}'\n");
}

TEST(LexerSuite, If) {
  std::stringstream in(
      "if ($numberA % $i == 0 && $numberB % $i == 0) {\n"
      "    $nod = $i;\n"
      "    break;\n"
      "}");

  std::stringstream out;
  dump_tokens(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>	If 'if'\n"
      "Loc=<1:3>	L_Paren '('\n"
      "Loc=<1:4>	Dollar '$'\n"
      "Loc=<1:5>\tId 'numberA'\n"
      "Loc=<1:13>	Mod '%'\n"
      "Loc=<1:15>	Dollar '$'\n"
      "Loc=<1:16>	Id 'i'\n"
      "Loc=<1:18>	Equality '='\n"
      "Loc=<1:19>	Equality '='\n"
      "Loc=<1:21>	Value '0'\n"
      "Loc=<1:23>	And '&&'\n"
      "Loc=<1:26>	Dollar '$'\n"
      "Loc=<1:27>	Id 'numberB'\n"
      "Loc=<1:35>	Mod '%'\n"
      "Loc=<1:37>	Dollar '$'\n"
      "Loc=<1:38>	Id 'i'\n"
      "Loc=<1:40>	Equality '='\n"
      "Loc=<1:41>	Equality '='\n"
      "Loc=<1:43>	Value '0'\n"
      "Loc=<1:44>	R_Paren ')'\n"
      "Loc=<1:46>	L_Brace '{'\n"
      "Loc=<2:4>	Dollar '$'\n"
      "Loc=<2:5>	Id 'nod'\n"
      "Loc=<2:9>	Equality '='\n"
      "Loc=<2:11>	Dollar '$'\n"
      "Loc=<2:12>	Id 'i'\n"
      "Loc=<2:13>	Semicolon ';'\n"
      "Loc=<3:4>	Break 'break'\n"
      "Loc=<3:9>	Semicolon ';'\n"
      "Loc=<4:0>	R_Brace '}'\n");
}

TEST(LexerSuite, Echo) {
  std::stringstream in("echo \" наименьшое число \" . $min;");

  std::stringstream out;
  dump_tokens(in, out);

  EXPECT_EQ(
      out.str(),
      "Loc=<1:0>	Echo 'echo'\n"
      "Loc=<1:5>	String '\" наименьшое число \"'\n"
      "Loc=<1:26>	Point '.'\n"
      "Loc=<1:28>	Dollar '$'\n"
      "Loc=<1:29>	Id 'min'\n"
      "Loc=<1:32>	Semicolon ';'\n");
}

}  // namespace php::test