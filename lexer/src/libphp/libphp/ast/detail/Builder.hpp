#pragma once

#include <libphp/ast/Ast.hpp>
#include <libphp/parser.hpp>

#include <PhpParserBaseVisitor.h>

#include <any>

namespace php::ast::detail {

class Builder final : public PhpParserBaseVisitor {
 public:
  explicit Builder(ast::Document& document) : document_(document) {}

  std::any visitDocument(PhpParser::DocumentContext* context) override;
  std::any visitElements(PhpParser::ElementsContext* context) override;
  std::any visitStatement(PhpParser::StatementContext* context) override;
  std::any visitColonizedElement(
      PhpParser::ColonizedElementContext* context) override;
  std::any visitAssigned(PhpParser::AssignedContext* context) override;
  std::any visitExpression(PhpParser::ExpressionContext* context) override;

 private:
  ast::Document& document_;
};

}  // namespace php::ast::detail
