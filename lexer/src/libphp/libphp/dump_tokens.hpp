#pragma once

#include <iosfwd>

namespace php {

void dump_tokens(std::istream& in, std::ostream& out);

}  // namespace php