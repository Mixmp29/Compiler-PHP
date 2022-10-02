#include <libphp/dump_symtable.hpp>
#include <libphp/dump_tokens.hpp>
#include <libphp/parser.hpp>

#include <PhpLexer.h>
#include <antlr4-runtime.h>
#include <cxxopts.hpp>

#include <fstream>
#include <iostream>
#include <string>

const char* const file_path_opt = "file_path";
const char* const dump_tokens_opt = "dump-tokens";
const char* const dump_ast_opt = "dump-ast";
const char* const dump_symtable_opt = "dump-symtable";

int main(int argc, char** argv) {
  cxxopts::Options options("php-parser", "ANTLR4 php parser example");

  options.positional_help("<file_path>");

  try {
    // clang-format off
    options.add_options()
        (file_path_opt, "", cxxopts::value<std::string>())
        (dump_tokens_opt, "")
        (dump_ast_opt, "")
        (dump_symtable_opt, "")
        ("h,help", "Print help");
    // clang-format on
  } catch (const cxxopts::OptionSpecException& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  options.parse_positional({file_path_opt});

  try {
    const auto result = options.parse(argc, argv);

    if (result.count("help") > 0 || result.count(file_path_opt) != 1) {
      std::cout << options.help() << "\n";
      return 0;
    }

    std::ifstream input_stream(result[file_path_opt].as<std::string>());

    if (!input_stream.good()) {
      std::cerr << "Unable to read stream\n";
      return 1;
    }

    antlr4::ANTLRInputStream antlr_stream(input_stream);
    PhpLexer lexer(&antlr_stream);
    if (result.count(dump_tokens_opt) > 0) {
      php::dump_tokens(lexer, std::cout);
      return 0;
    }
    auto parser_result = php::parse(lexer);
    if (result.count(dump_ast_opt) > 0) {
      if (parser_result.errors_.empty()) {
        php::dump_ast(parser_result.document_, std::cout);
      }
    }
    if (!parser_result.errors_.empty()) {
      php::dump_errors(parser_result.errors_, std::cerr);
      return 1;
    }

    if (result.count(dump_symtable_opt) > 0) {
      php::ast::SymTable symtable;
      php::ast::Errors errors;
      php::create_symtable(parser_result.document_, symtable, errors);
      php::dump_symtable(symtable, std::cout);
      php::dump_symtable_errors(errors, std::cout);
    }

  } catch (const cxxopts::OptionException& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
