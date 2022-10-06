#pragma once

#include <libphp/ast/Symbol.hpp>
#include <libphp/ast/Visitor.hpp>

#include <ostream>
#include <unordered_map>
#include <vector>

namespace php::ast {

struct Error {
  int line;
  int column;
  std::string msg;
};

using Errors = std::vector<Error>;

using SymTable = std::unordered_map<std::string, Symbol>;

class SymTableVisitor final : public Visitor {
 public:
  SymTableVisitor(SymTable& symtable, Errors& errors)
      : symtable_(symtable), type_handler_(errors) {}

  static void exec(Document& document, SymTable& symtable, Errors& errors);

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
  void update_symtable(
      const std::string& id,
      Symbol::Type type,
      int line,
      int column);

  class TypeHandler final {
   public:
    TypeHandler(Errors& errors) : errors_(errors) {}
    void reset_type();
    void set_integer(int line, int column);
    void set_string(int line, int column);

    Symbol::Type get_type() const;

    void update_type(Symbol::Type new_type, int line, int column);

   private:
    Errors& errors_;
    Symbol::Type current_type_ = Symbol::Type::Unsetted;
  };

  SymTable& symtable_;
  TypeHandler type_handler_;
};

}  // namespace php::ast
