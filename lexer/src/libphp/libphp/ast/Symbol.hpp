#pragma once

#include <string>

namespace php::ast {

class Symbol {
 public:
  enum Type {
    String,
    Integer,
    Error,
    Unsetted,
  };
  Symbol(Type type) : type_(type) {}
  Type get_type() const { return type_; }
  void set_type(Type type) { type_ = type; }

  std::string get_str_type() const {
    switch (type_) {
      case Type::String:
        return std::string("string");
      case Type::Integer:
        return std::string("integer");
      case Type::Error:
        return std::string("error");
      case Type::Unsetted:
        return std::string("unsetted");
    }
    return std::string("undefined");
  }

 private:
  Type type_;
};

}  // namespace php::ast
