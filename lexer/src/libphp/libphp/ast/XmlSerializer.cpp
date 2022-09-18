#include <libphp/ast/XmlSerializer.hpp>

#include <string>

namespace php::ast {

void XmlSerializer::exec(Document& document, std::ostream& out) {
  XmlSerializer xml_serializer;
  xml_serializer.nodes_.push(xml_serializer.doc_.append_child("php"));
  document.get_value()->accept(xml_serializer);
  xml_serializer.doc_.save(out, "  ");
}

void XmlSerializer::visit(Elements& value) {
  for (const auto& object : value.value()) {
    object->accept(*this);
  }
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
  value.value()->accept(*this);
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

void XmlSerializer::visit(IfState& value) {
  auto code = append_child("if");
  nodes_.push(code);
  value.comparison()->accept(*this);
  value.codeBlock()->accept(*this);
  nodes_.pop();
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
  append_text(value.name().c_str());
}

void XmlSerializer::visit(Condition& value) {
  append_text(value.name().c_str());
}

pugi::xml_node XmlSerializer::append_child(const char* name) {
  return nodes_.top().append_child(name);
}

void XmlSerializer::append_text(const char* text) {
  auto text_node = nodes_.top().append_child(pugi::node_pcdata);
  text_node.set_value(text);
}

}  // namespace php::ast
