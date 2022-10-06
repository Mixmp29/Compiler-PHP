#pragma once

#include <PhpLexer.h>

#include <iosfwd>

namespace php {

void dump_tokens(PhpLexer& lexer, std::ostream& out);

}  // namespace php