#pragma once

#include <libphp/ast/SymTableVisitor.hpp>
#include <libphp/parser.hpp>

#include <iosfwd>

namespace php {

void create_symtable(
    ast::Document& document,
    ast::SymTable& sym_table,
    ast::Errors& errors);

void dump_symtable(ast::SymTable& sym_table, std::ostream& out);

void dump_symtable_errors(ast::Errors& errors, std::ostream& out);

}  // namespace php
