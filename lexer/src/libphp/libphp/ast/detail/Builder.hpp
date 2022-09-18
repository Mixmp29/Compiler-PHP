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
  std::any visitEcho(PhpParser::EchoContext* context) override;
  std::any visitPrint(PhpParser::PrintContext* context) override;
  std::any visitIfState(PhpParser::IfStateContext* context) override;
  std::any visitAssigned(PhpParser::AssignedContext* context) override;
  std::any visitCodeBlock(PhpParser::CodeBlockContext* context) override;
  std::any visitOpExpr(PhpParser::OpExprContext* context) override;
  std::any visitStrExpr(PhpParser::StrExprContext* context) override;
  std::any visitUPostExpr(PhpParser::UPostExprContext* context) override;
  std::any visitUPrefExpr(PhpParser::UPrefExprContext* context) override;
  std::any visitParenExpr(PhpParser::ParenExprContext* context) override;
  std::any visitAtomExpr(PhpParser::AtomExprContext* context) override;
  std::any visitComparison(PhpParser::ComparisonContext* context) override;
  std::any visitVar(PhpParser::VarContext* context) override;
  std::any visitCondition(PhpParser::ConditionContext* context) override;

 private:
  ast::Document& document_;
};

}  // namespace php::ast::detail
