#pragma once

#include <libphp/ast/Ast.hpp>

namespace php::ast {

class Visitor {
 public:
  virtual void visit(Elements& value) = 0;
  virtual void visit(Statement& value) = 0;
  virtual void visit(Assigned& value) = 0;
  virtual void visit(Expression& value) = 0;
  /* virtual void visit(Array& value) = 0;
  virtual void visit(String& value) = 0;
  virtual void visit(Number& value) = 0; */
};

}  // namespace php::ast
