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
  auto* value = std::any_cast<Node*>(visitChildren(context->assigned()));
  return static_cast<Node*>(document_.create_node<Statement>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitAssigned(PhpParser::AssignedContext* context) {
  auto* value = std::any_cast<Node*>(visitChildren(context->expression()));
  return static_cast<Node*>(document_.create_node<Assigned>(
      value,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

std::any Builder::visitExpression(PhpParser::ExpressionContext* context) {
  auto name = context->getText();
  return static_cast<Node*>(document_.create_node<Expression>(
      name,
      context->getStart()->getLine(),
      context->getStart()->getCharPositionInLine()));
}

}  // namespace php::ast::detail
