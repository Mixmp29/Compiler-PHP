#pragma once

#include <libphp/ast/Visitor.hpp>

#include <pugixml.hpp>

#include <ostream>
#include <stack>

namespace php::ast {

class XmlSerializer final : public Visitor {
 public:
  static void exec(Document& document, std::ostream& out);

  void visit(Elements& value) override;
  void visit(Statement& value) override;
  void visit(ElementWithColon& value) override;
  void visit(Echo& value) override;
  void visit(Print& value) override;
  void visit(Assigned& value) override;
  void visit(CodeBlock& value) override;
  void visit(OpExpr& value) override;
  void visit(StrExpr& value) override;
  void visit(UPostExpr& value) override;
  void visit(UPrefExpr& value) override;
  void visit(ParenExpr& value) override;
  void visit(AtomExpr& value) override;
  void visit(Var& value) override;

 private:
  pugi::xml_node append_child(const char* name);
  void append_text(const char* text);

  pugi::xml_document doc_;
  std::stack<pugi::xml_node> nodes_;
};

}  // namespace php::ast
