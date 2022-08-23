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

void XmlSerializer::visit(Assigned& value) {
  auto code = append_child(" command ");
  nodes_.push(code);
  value.value()->accept(*this);
  nodes_.pop();
}

pugi::xml_node XmlSerializer::append_child(const char* name) {
  return nodes_.top().append_child(name);
}

void XmlSerializer::append_text(const char* text) {
  auto text_node = nodes_.top().append_child(pugi::node_pcdata);
  text_node.set_value(text);
}

void XmlSerializer::visit(Expression& value) {
  append_text(value.name().c_str());
}

}  // namespace php::ast
