#include <libphp/ast/detail/Builder.hpp>

namespace php::ast::detail {

std::any Builder::visitDocument(PhpParser::DocumentContext* context) {
  auto* value = std::any_cast<Node*>(visit(context->elements()));
  document_.set_value(value);
  return value;
}

std::any Builder::visitElements(PhpParser::ElementsContext* context) {
  Elements::ValueType elements;
  for (const auto& statement : context->statement()) {
    elements.push_back(std::any_cast<Node*>(visit(statement)));
  }
  return static_cast<Node*>(document_.create_node<Elements>(
      elements,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitStatement(PhpParser::StatementContext* context) {
  auto* value = std::any_cast<Node*>(visitChildren(context));
  return static_cast<Node*>(document_.create_node<Statement>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitColonizedElement(
    PhpParser::ColonizedElementContext* context) {
  auto* value =
      std::any_cast<Node*>(visitChildren(context->elementWithColon()));
  return static_cast<Node*>(document_.create_node<ElementWithColon>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitEcho(PhpParser::EchoContext* context) {
  auto* value = std::any_cast<Node*>(visitChildren(context));
  return static_cast<Node*>(document_.create_node<Echo>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitPrint(PhpParser::PrintContext* context) {
  auto* value = std::any_cast<Node*>(visitChildren(context));
  return static_cast<Node*>(document_.create_node<Print>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitInput(PhpParser::InputContext* context) {
  return static_cast<Node*>(document_.create_node<Input>(
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitIfElse(PhpParser::IfElseContext* context) {
  auto* ifState = std::any_cast<Node*>(visit(context->ifState()));
  auto* elseState = std::any_cast<Node*>(visit(context->elseState()));
  return static_cast<Node*>(document_.create_node<IfElse>(
      ifState,
      elseState,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitIfState(PhpParser::IfStateContext* context) {
  auto* comparison = std::any_cast<Node*>(visit(context->comparison()));
  auto* codeBlock = std::any_cast<Node*>(visit(context->codeBlock()));
  return static_cast<Node*>(document_.create_node<IfState>(
      comparison,
      codeBlock,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitElseState(PhpParser::ElseStateContext* context) {
  auto* codeBlock = std::any_cast<Node*>(visit(context->codeBlock()));
  return static_cast<Node*>(document_.create_node<ElseState>(
      codeBlock,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitWhileState(PhpParser::WhileStateContext* context) {
  auto* comparison = std::any_cast<Node*>(visit(context->comparison()));
  auto* codeBlock = std::any_cast<Node*>(visit(context->codeBlock()));
  return static_cast<Node*>(document_.create_node<WhileState>(
      comparison,
      codeBlock,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitAssigned(PhpParser::AssignedContext* context) {
  auto* var = std::any_cast<Node*>(visit(context->var()));
  auto* val = std::any_cast<Node*>(visit(context->expr()));
  return static_cast<Node*>(document_.create_node<Assigned>(
      var,
      val,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitCodeBlock(PhpParser::CodeBlockContext* context) {
  auto* value = std::any_cast<Node*>(visit(context->elements()));
  return static_cast<Node*>(document_.create_node<CodeBlock>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitOpExpr(PhpParser::OpExprContext* context) {
  auto* lhs = std::any_cast<Node*>(visit(context->left));
  auto op = context->op->getText();
  auto* rhs = std::any_cast<Node*>(visit(context->right));
  return static_cast<Node*>(document_.create_node<OpExpr>(
      lhs,
      op,
      rhs,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitStrExpr(PhpParser::StrExprContext* context) {
  auto* lhs = std::any_cast<Node*>(visit(context->left));
  auto op = context->op->getText();
  auto* rhs = std::any_cast<Node*>(visit(context->right));
  return static_cast<Node*>(document_.create_node<StrExpr>(
      lhs,
      op,
      rhs,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitUPostExpr(PhpParser::UPostExprContext* context) {
  auto* value = std::any_cast<Node*>(visit(context->var()));
  auto op = context->op->getText();
  return static_cast<Node*>(document_.create_node<UPostExpr>(
      value,
      op,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitUPrefExpr(PhpParser::UPrefExprContext* context) {
  auto* value = std::any_cast<Node*>(visit(context->var()));
  auto op = context->op->getText();
  return static_cast<Node*>(document_.create_node<UPrefExpr>(
      value,
      op,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitParenExpr(PhpParser::ParenExprContext* context) {
  auto* value = std::any_cast<Node*>(visit(context->expr()));
  return static_cast<Node*>(document_.create_node<ParenExpr>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitAtomExpr(PhpParser::AtomExprContext* context) {
  auto* value = std::any_cast<Node*>(visit(context->var()));
  return static_cast<Node*>(document_.create_node<AtomExpr>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitComparison(PhpParser::ComparisonContext* context) {
  auto* lhs = std::any_cast<Node*>(visit(context->left));
  auto* rhs = std::any_cast<Node*>(visit(context->right));
  auto* op = std::any_cast<Node*>(visit(context->condition()));
  return static_cast<Node*>(document_.create_node<Comparison>(
      lhs,
      op,
      rhs,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitVar(PhpParser::VarContext* context) {
  auto* value = std::any_cast<Node*>(visitChildren(context));
  return static_cast<Node*>(document_.create_node<Var>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitCondition(PhpParser::ConditionContext* context) {
  auto name = context->getText();
  return static_cast<Node*>(document_.create_node<Condition>(
      name,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitId(PhpParser::IdContext* context) {
  auto name = context->getText();
  return static_cast<Node*>(document_.create_node<Id>(
      name,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitValue(PhpParser::ValueContext* context) {
  auto name = context->getText();
  return static_cast<Node*>(document_.create_node<Value>(
      name,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitStr(PhpParser::StrContext* context) {
  auto name = context->getText();
  return static_cast<Node*>(document_.create_node<Str>(
      name,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

}  // namespace php::ast::detail