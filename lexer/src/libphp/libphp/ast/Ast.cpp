#include <libphp/ast/Ast.hpp>

#include <libphp/ast/Visitor.hpp>

namespace php::ast {

void Elements::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void Statement::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void ElementWithColon::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void Assigned::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void Expression::accept(Visitor& visitor) {
  visitor.visit(*this);
}

}  // namespace php::ast
