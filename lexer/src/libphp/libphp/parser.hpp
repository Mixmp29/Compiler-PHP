#pragma once

#include <libphp/ast/Ast.hpp>

#include <PhpLexer.h>

#include <iosfwd>

namespace php {

struct Error {
  size_t line_;
  size_t column_;
  std::string message_;
};

using Errors = std::vector<Error>;

struct ParseResult {
  static ParseResult document(ast::Document document) {
    ParseResult result;
    result.document_ = std::move(document);
    return result;
  }

  static ParseResult errors(Errors errors) {
    ParseResult result;
    result.errors_ = std::move(errors);
    return result;
  }

  ast::Document document_;
  Errors errors_;
};

ParseResult parse(PhpLexer& lexer);

void dump_ast(ast::Document& document, std::ostream& out);

void dump_errors(
    const Errors& errors,
    std::ostream& out /*, std::istream& in*/);

}  // namespace php
