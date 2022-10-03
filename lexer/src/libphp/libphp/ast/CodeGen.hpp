#pragma once

#include <libphp/ast/SymTableVisitor.hpp>
#include <libphp/ast/Visitor.hpp>

#include <ostream>
#include <sstream>
#include <stack>
#include <unordered_map>

namespace php::ast {

class CodeGen final : public Visitor {
 public:
  CodeGen(SymTable& symtable, std::ostream& out)
      : symtable_(symtable), out_(out) {}

  static void exec(Document& document, SymTable& symtable, std::ostream& out);

  void generate();

  void visit(Elements& value) override;
  void visit(Statement& value) override;
  void visit(ElementWithColon& value) override;
  void visit(Echo& value) override;
  void visit(Print& value) override;
  void visit(Input& value) override;
  void visit(IfElse& value) override;
  void visit(IfState& value) override;
  void visit(ElseState& value) override;
  void visit(WhileState& value) override;
  void visit(Assigned& value) override;
  void visit(CodeBlock& value) override;
  void visit(OpExpr& value) override;
  void visit(StrExpr& value) override;
  void visit(UPostExpr& value) override;
  void visit(UPrefExpr& value) override;
  void visit(ParenExpr& value) override;
  void visit(AtomExpr& value) override;
  void visit(Comparison& value) override;
  void visit(Var& value) override;
  void visit(Condition& value) override;
  void visit(Id& value) override;
  void visit(Value& value) override;
  void visit(Str& value) override;

 private:
  int pop_value();
  void push_value(int val);

  struct GenerateFlags {
    bool print_string = false;
    bool print_int = false;
    bool read_string = false;
    bool read_int = false;
    bool string = false;
  };

  struct States {
    bool var = false;
    bool ifelse = false;
    bool string = false;
  };

  int var_num_ = 0;
  GenerateFlags generate_flags_;
  States states_;
  std::stack<int> values_;
  std::unordered_map<std::string, int> ids_;
  SymTable& symtable_;
  std::ostream& out_;
  std::stringstream body_;
  int else_label_;
};

}  // namespace php::ast
