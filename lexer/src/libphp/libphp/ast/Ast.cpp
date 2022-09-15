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

void Echo::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void Print::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void Assigned::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void CodeBlock::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void OpExpr::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void StrExpr::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void UPostExpr::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void UPrefExpr::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void ParenExpr::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void AtomExpr::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void Var::accept(Visitor& visitor) {
  visitor.visit(*this);
}

}  // namespace php::ast
