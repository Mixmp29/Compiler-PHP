#include <libphp/ast/XmlSerializer.hpp>

#include <string>

namespace php::ast {

void XmlSerializer::exec(Document& document, std::ostream& out) {
  XmlSerializer xml_serializer;
  xml_serializer.nodes_.push(xml_serializer.doc_.append_child("php"));
  document.get_node()->accept(xml_serializer);
  xml_serializer.doc_.save(out, "  ");
}

void XmlSerializer::visit(Elements& value) {
  auto code = append_child("elements");
  nodes_.push(code);
  for (const auto& statement : value.value()) {
    statement->accept(*this);
  }
  nodes_.pop();
}

void XmlSerializer::visit(Statement& value) {
  value.value()->accept(*this);
}

void XmlSerializer::visit(ElementWithColon& value) {
  auto code = append_child("command");
  nodes_.push(code);
  value.value()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(Echo& value) {
  auto code = append_child("echo");
  nodes_.push(code);
  value.value()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(Print& value) {
  auto code = append_child("print");
  nodes_.push(code);
  value.value()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(Input& /*value*/) {
  append_text("input");
}

void XmlSerializer::visit(IfElse& value) {
  auto code = append_child("if_else_state");
  nodes_.push(code);
  value.ifState()->accept(*this);
  value.elseState()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(IfState& value) {
  auto code = append_child("if");
  nodes_.push(code);
  value.comparison()->accept(*this);
  value.codeBlock()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(ElseState& value) {
  auto code = append_child("else");
  nodes_.push(code);
  value.codeBlock()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(WhileState& value) {
  auto code = append_child("while");
  nodes_.push(code);
  value.comparison()->accept(*this);
  value.codeBlock()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(Assigned& value) {
  auto code = append_child("assign");
  nodes_.push(code);
  value.var()->accept(*this);
  append_text(" = ");
  value.val()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(CodeBlock& value) {
  auto code = append_child("code_block");
  nodes_.push(code);
  value.elements()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(OpExpr& value) {
  append_text("(");
  value.lhs()->accept(*this);
  append_text(" ");
  append_text(value.op().c_str());
  append_text(" ");
  value.rhs()->accept(*this);
  append_text(")");
}

void XmlSerializer::visit(StrExpr& value) {
  append_text("(");
  value.lhs()->accept(*this);
  append_text(" ");
  append_text(value.op().c_str());
  append_text(" ");
  value.rhs()->accept(*this);
  append_text(")");
}

void XmlSerializer::visit(UPostExpr& value) {
  append_text("(");
  value.value()->accept(*this);
  append_text(value.op().c_str());
  append_text(")");
}

void XmlSerializer::visit(UPrefExpr& value) {
  append_text("(");
  append_text(value.op().c_str());
  value.value()->accept(*this);
  append_text(")");
}

void XmlSerializer::visit(ParenExpr& value) {
  value.value()->accept(*this);
}

void XmlSerializer::visit(AtomExpr& value) {
  value.value()->accept(*this);
}

void XmlSerializer::visit(Comparison& value) {
  auto code = append_child("comparison");
  nodes_.push(code);
  value.lhs()->accept(*this);
  append_text(" ");
  value.op()->accept(*this);
  append_text(" ");
  value.rhs()->accept(*this);
  nodes_.pop();
}

void XmlSerializer::visit(Var& value) {
  value.value()->accept(*this);
}

void XmlSerializer::visit(Condition& value) {
  append_text(value.comp().c_str());
}

void XmlSerializer::visit(Id& value) {
  append_text(value.name().c_str());
}

void XmlSerializer::visit(Value& value) {
  append_text(value.integer().c_str());
}

void XmlSerializer::visit(Str& value) {
  append_text(value.text().c_str());
}

pugi::xml_node XmlSerializer::append_child(const char* name) {
  return nodes_.top().append_child(name);
}

void XmlSerializer::append_text(const char* text) {
  auto text_node = nodes_.top().append_child(pugi::node_pcdata);
  text_node.set_value(text);
}

}  // namespace php::ast
