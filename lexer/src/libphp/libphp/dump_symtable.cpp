#include <libphp/dump_symtable.hpp>
#include <libphp/parser.hpp>

#include <fmt/format.h>

namespace php {

void create_symtable(
    ast::Document& document,
    ast::SymTable& sym_table,
    ast::Errors& errors) {
  ast::SymTableVisitor::exec(document, sym_table, errors);
}

void dump_symtable(ast::SymTable& sym_table, std::ostream& out) {
  for (const auto& sym : sym_table) {
    out << sym.first << "   " << sym.second.get_str_type() << std::endl;
  }
}

void dump_symtable_errors(ast::Errors& errors, std::ostream& out) {
  for (const auto& error : errors) {
    out << fmt::format("{}:{} {}\n", error.line, error.column, error.msg);
  }
}

}  // namespace php
