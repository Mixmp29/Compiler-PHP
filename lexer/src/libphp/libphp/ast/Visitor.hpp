#pragma once

#include <libphp/ast/Ast.hpp>

namespace php::ast {

class Visitor {
 public:
  virtual void visit(Elements& value) = 0;
  virtual void visit(Statement& value) = 0;
  virtual void visit(ElementWithColon& value) = 0;
  virtual void visit(Echo& value) = 0;
  virtual void visit(Print& value) = 0;
  virtual void visit(Input& value) = 0;
  virtual void visit(IfElse& value) = 0;
  virtual void visit(IfState& value) = 0;
  virtual void visit(ElseState& value) = 0;
  virtual void visit(WhileState& value) = 0;
  virtual void visit(Assigned& value) = 0;
  virtual void visit(CodeBlock& value) = 0;
  virtual void visit(OpExpr& value) = 0;
  virtual void visit(StrExpr& value) = 0;
  virtual void visit(UPostExpr& value) = 0;
  virtual void visit(UPrefExpr& value) = 0;
  virtual void visit(ParenExpr& value) = 0;
  virtual void visit(AtomExpr& value) = 0;
  virtual void visit(Comparison& value) = 0;
  virtual void visit(Var& value) = 0;
  virtual void visit(Condition& value) = 0;
  virtual void visit(Id& value) = 0;
  virtual void visit(Value& value) = 0;
  virtual void visit(Str& value) = 0;
};

}  // namespace php::ast
