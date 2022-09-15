#pragma once

#include <libphp/ast/Ast.hpp>

namespace php::ast {

class Visitor {
 public:
  virtual void visit(Elements& value) = 0;
  virtual void visit(Statement& value) = 0;
  virtual void visit(ElementWithColon& value) = 0;
  virtual void visit(Assigned& value) = 0;
  virtual void visit(OpExpr& value) = 0;
  virtual void visit(StrExpr& value) = 0;
  virtual void visit(UPostExpr& value) = 0;
  virtual void visit(UPrefExpr& value) = 0;
  virtual void visit(ParenExpr& value) = 0;
  virtual void visit(AtomExpr& value) = 0;
  virtual void visit(Var& value) = 0;
};

}  // namespace php::ast
