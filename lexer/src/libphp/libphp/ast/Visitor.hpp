#pragma once

#include <libphp/ast/Ast.hpp>

namespace php::ast {

class Visitor {
 public:
  virtual void visit(Elements& value) = 0;
  virtual void visit(Statement& value) = 0;
  virtual void visit(ElementWithColon& value) = 0;
  virtual void visit(Assigned& value) = 0;
  virtual void visit(Expression& value) = 0;
};

}  // namespace php::ast
