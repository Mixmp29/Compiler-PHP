#include <gtest/gtest.h>

#include <libphp/dump_symtable.hpp>
#include <libphp/parser.hpp>

#include <sstream>
#include <string>

namespace php::test {

void get_symtable_from_stream(std::istream& in, std::ostream& out) {
  antlr4::ANTLRInputStream stream(in);
  PhpLexer lexer(&stream);
  auto parser_result = php::parse(lexer);
  if (!parser_result.errors_.empty()) {
    php::dump_errors(parser_result.errors_, out);
  }
  php::ast::SymTable symtable;
  php::ast::Errors errors;
  php::create_symtable(parser_result.document_, symtable, errors);
  php::dump_symtable(symtable, out);
  php::dump_symtable_errors(errors, out);
}

TEST(SymTableSuite, CorrectEx) {
  std::stringstream in(
      "<\?php\n"
      " $min = 10000;\n"
      " $A = \"string\";\n"
      " $B = 21;\n"
      " $C = $B + $min;\n"
      " $D = $C + 12;\n"
      " $i = 0;\n"
      "\?>");
  std::stringstream out;
  get_symtable_from_stream(in, out);

  EXPECT_EQ(
      "$i   integer\n"
      "$D   integer\n"
      "$C   integer\n"
      "$B   integer\n"
      "$A   string\n"
      "$min   integer\n",
      out.str());
}

TEST(SymTableSuite, IncorrectEx) {
  std::stringstream in(
      "<\?php\n"
      " $A = 1;\n"
      " $B = \"1\";\n"
      " $F = $A * $B;\n"
      " $D = 1;\n"
      " $C = \"2\";\n"
      " $D = $C;\n"
      "\?>");
  std::stringstream out;
  get_symtable_from_stream(in, out);

  EXPECT_EQ(
      "$C   string\n"
      "$D   integer\n"
      "$F   error\n"
      "$B   error\n"
      "$A   integer\n"
      "4:11 type detection error\n",
      out.str());
}

TEST(SymTableSuite, String) {
  std::stringstream in(
      "<\?php\n"
      " $A = \"str\";\n"
      " $B = $A;\n"
      " $D = \"1\";\n"
      " $C = \"2\";\n"
      " $D = $C;\n"
      "\?>");
  std::stringstream out;
  get_symtable_from_stream(in, out);

  EXPECT_EQ(
      "$C   string\n"
      "$D   string\n"
      "$B   unsetted\n"
      "$A   string\n",
      out.str());
}

}  // namespace php::test
