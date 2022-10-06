#include <libphp/parser.hpp>

#include <libphp/ast/XmlSerializer.hpp>
#include <libphp/ast/detail/Builder.hpp>

#include <PhpParser.h>

#include <fmt/format.h>

namespace php {

namespace {

class StreamErrorListener : public antlr4::BaseErrorListener {
 public:
  void syntaxError(
      antlr4::Recognizer* /*recognizer*/,
      antlr4::Token* /*offendingSymbol*/,
      size_t line,
      size_t column,
      const std::string& message,
      std::exception_ptr /*e*/) override {
    errors_.emplace_back(Error{line, column, message});
  }

  const Errors& errors() const { return errors_; }

 private:
  Errors errors_;
};

}  // namespace

ParseResult parse(PhpLexer& lexer) {
  antlr4::CommonTokenStream tokens(&lexer);
  PhpParser parser(&tokens);

  StreamErrorListener error_listener;
  parser.removeErrorListeners();
  parser.addErrorListener(&error_listener);

  auto* document_parse_tree = parser.document();

  const auto& errors = error_listener.errors();
  if (!errors.empty()) {
    return ParseResult::errors(errors);
  }

  ast::Document document;
  ast::detail::Builder builder(document);
  builder.visit(document_parse_tree);

  return ParseResult::document(std::move(document));
}

void dump_ast(ast::Document& document, std::ostream& out) {
  ast::XmlSerializer::exec(document, out);
}

void dump_errors(const Errors& errors, std::ostream& out) {
  for (const auto& error : errors) {
    out << fmt::format(
        "{}:{} {}\n", error.line_, error.column_, error.message_);
  }
}

}  // namespace php