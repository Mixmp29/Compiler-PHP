#include <libphp/ast/SymTableVisitor.hpp>
#include <string>

namespace php::ast {

void SymTableVisitor::exec(
    Document& document,
    SymTable& symtable,
    Errors& errors) {
  SymTableVisitor symtable_visitor(symtable, errors);
  document.get_node()->accept(symtable_visitor);  // <- а потом вроде тут
}

void SymTableVisitor::visit(Elements& value) {
  for (const auto& statement : value.value()) {
    statement->accept(*this);
  }
}

void SymTableVisitor::visit(Statement& value) {
  type_handler_.reset_type();

  value.value()->accept(*this);
}

void SymTableVisitor::visit(ElementWithColon& value) {
  value.value()->accept(*this);
}
void SymTableVisitor::visit(Echo& value) {
  value.value()->accept(*this);
}
void SymTableVisitor::visit(Print& value) {
  value.value()->accept(*this);
}
void SymTableVisitor::visit(Input& value) {
  type_handler_.set_integer(value.get_line(), value.get_column());
}
void SymTableVisitor::visit(IfElse& value) {
  value.ifState()->accept(*this);
  value.elseState()->accept(*this);
}
void SymTableVisitor::visit(IfState& value) {
  value.comparison()->accept(*this);
  value.codeBlock()->accept(*this);
}
void SymTableVisitor::visit(ElseState& value) {
  value.codeBlock()->accept(*this);
}
void SymTableVisitor::visit(WhileState& value) {
  value.comparison()->accept(*this);
  value.codeBlock()->accept(*this);
}
void SymTableVisitor::visit(Assigned& value) {
  value.val()->accept(*this);
  value.var()->accept(*this);
}
void SymTableVisitor::visit(CodeBlock& value) {
  value.elements()->accept(*this);
}
void SymTableVisitor::visit(OpExpr& value) {
  type_handler_.set_integer(value.get_line(), value.get_column());

  value.lhs()->accept(*this);
  value.rhs()->accept(*this);
}
void SymTableVisitor::visit(StrExpr& value) {
  type_handler_.set_string(value.get_line(), value.get_column());

  value.lhs()->accept(*this);
  value.rhs()->accept(*this);
}
void SymTableVisitor::visit(UPostExpr& value) {
  type_handler_.set_integer(value.get_line(), value.get_column());

  value.value()->accept(*this);
}
void SymTableVisitor::visit(UPrefExpr& value) {
  value.value()->accept(*this);

  type_handler_.set_integer(value.get_line(), value.get_column());
}
void SymTableVisitor::visit(ParenExpr& value) {
  type_handler_.set_integer(value.get_line(), value.get_column());

  value.value()->accept(*this);
}
void SymTableVisitor::visit(AtomExpr& value) {
  value.value()->accept(*this);
}
void SymTableVisitor::visit(Comparison& value) {
  value.op()->accept(*this);
  value.lhs()->accept(*this);
  value.rhs()->accept(*this);
}
void SymTableVisitor::visit(Var& value) {
  value.value()->accept(*this);
}
void SymTableVisitor::visit(Condition& value) {
  type_handler_.set_integer(value.get_line(), value.get_column());
}
void SymTableVisitor::visit(Id& value) {
  update_symtable(
      value.name(),
      type_handler_.get_type(),
      value.get_line(),
      value.get_column());
}
void SymTableVisitor::visit(Value& value) {
  type_handler_.set_integer(value.get_line(), value.get_column());
}
void SymTableVisitor::visit(Str& value) {
  type_handler_.set_string(value.get_line(), value.get_column());
}

void SymTableVisitor::update_symtable(
    const std::string& id,
    Symbol::Type type,
    int line,
    int column) {
  auto value_it = symtable_.find(id);
  if (value_it == symtable_.end()) {
    symtable_.insert({id, Symbol(type)});
    return;
  }

  if (type == Symbol::Type::Unsetted) {
    return;
  }

  Symbol::Type cur_type = value_it->second.get_type();

  if (cur_type == Symbol::Type::Unsetted) {
    value_it->second.set_type(type);
    return;
  }

  if (cur_type != type) {
    type_handler_.update_type(Symbol::Type::Error, line, column);
    value_it->second.set_type(type_handler_.get_type());
  }
}

void SymTableVisitor::TypeHandler::reset_type() {
  current_type_ = Symbol::Type::Unsetted;
}

void SymTableVisitor::TypeHandler::set_integer(int line, int column) {
  update_type(Symbol::Type::Integer, line, column);
}

void SymTableVisitor::TypeHandler::set_string(int line, int column) {
  update_type(Symbol::Type::String, line, column);
}

Symbol::Type SymTableVisitor::TypeHandler::get_type() const {
  return current_type_;
}

void SymTableVisitor::TypeHandler::update_type(
    Symbol::Type new_type,
    int line,
    int column) {
  if (new_type == Symbol::Type::Error) {
    errors_.push_back({line, column, "type detection error"});
    current_type_ = Symbol::Type::Error;
    return;
  }
  if (current_type_ == Symbol::Type::Error) {
    return;
  }

  if (new_type == Symbol::Type::Unsetted) {
    return;
  }

  if (current_type_ == Symbol::Type::Unsetted) {
    current_type_ = new_type;
    return;
  }

  if (current_type_ != new_type) {
    errors_.push_back({line, column, "type detection error"});
    current_type_ = Symbol::Type::Error;
    return;
  }
}

}  // namespace php::ast
