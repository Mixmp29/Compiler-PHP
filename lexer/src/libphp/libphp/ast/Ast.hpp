#pragma once

#include <memory>
#include <vector>

namespace php::ast {

/* class String;
class Value; */
class Visitor;

class Node {
 public:
  Node(int line, int column) : line_(line), column_(column) {}
  virtual ~Node() = default;
  virtual void accept(Visitor& visitor) = 0;
  int get_line() const { return line_; }
  int get_column() const { return column_; }

 private:
  int line_;
  int column_;
};

class Document final {
 public:
  template <class T, class... Args>
  T* create_node(Args&&... args) {
    static_assert(std::is_base_of_v<Node, T>);
    values_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    return dynamic_cast<T*>(values_.back().get());
  }

  void set_value(ast::Node* value) { value_ = value; }
  ast::Node* get_value() const { return value_; }

 private:
  std::vector<std::unique_ptr<Node>> values_;
  ast::Node* value_ = nullptr;
};

class Elements final : public Node {
 public:
  using ValueType = std::vector<Node*>;

  explicit Elements(ValueType value, int line, int column)
      : Node(line, column), value_(std::move(value)) {}
  const ValueType& value() const { return value_; }
  void accept(Visitor& visitor) override;

 private:
  ValueType value_;
};

class Statement final : public Node {
 public:
  explicit Statement(Node* value, int line, int column)
      : Node(line, column), value_(value) {}
  Node* value() const { return value_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
};

class ElementWithColon final : public Node {
 public:
  explicit ElementWithColon(Node* value, int line, int column)
      : Node(line, column), value_(value) {}
  Node* value() const { return value_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
};

class Echo final : public Node {
 public:
  explicit Echo(Node* value, int line, int column)
      : Node(line, column), value_(value) {}
  Node* value() const { return value_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
};

class Print final : public Node {
 public:
  explicit Print(Node* value, int line, int column)
      : Node(line, column), value_(value) {}
  Node* value() const { return value_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
};

class Assigned final : public Node {
 public:
  explicit Assigned(Node* var, Node* val, int line, int column)
      : Node(line, column), var_(var), val_(val) {}
  Node* var() const { return var_; }
  Node* val() const { return val_; }
  void accept(Visitor& visitor) override;

 private:
  Node* var_;
  Node* val_;
};

class CodeBlock final : public Node {
 public:
  explicit CodeBlock(Node* value, int line, int column)
      : Node(line, column), value_(value) {}
  Node* value() const { return value_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
};

class OpExpr final : public Node {
 public:
  explicit OpExpr(Node* lhs, std::string& op, Node* rhs, int line, int column)
      : Node(line, column), lhs_(lhs), op_(std::move(op)), rhs_(rhs) {}
  Node* lhs() const { return lhs_; }
  const std::string& op() const { return op_; }
  Node* rhs() const { return rhs_; }
  void accept(Visitor& visitor) override;

 private:
  Node* lhs_;
  std::string op_;
  Node* rhs_;
};

class StrExpr final : public Node {
 public:
  explicit StrExpr(Node* lhs, std::string& op, Node* rhs, int line, int column)
      : Node(line, column), lhs_(lhs), op_(std::move(op)), rhs_(rhs) {}
  Node* lhs() const { return lhs_; }
  const std::string& op() const { return op_; }
  Node* rhs() const { return rhs_; }
  void accept(Visitor& visitor) override;

 private:
  Node* lhs_;
  std::string op_;
  Node* rhs_;
};

class UPostExpr final : public Node {
 public:
  explicit UPostExpr(Node* value, std::string& op, int line, int column)
      : Node(line, column), value_(value), op_(op) {}
  Node* value() const { return value_; }
  const std::string& op() const { return op_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
  std::string op_;
};

class UPrefExpr final : public Node {
 public:
  explicit UPrefExpr(Node* value, std::string& op, int line, int column)
      : Node(line, column), value_(value), op_(op) {}
  Node* value() const { return value_; }
  const std::string& op() const { return op_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
  std::string op_;
};

class ParenExpr final : public Node {
 public:
  explicit ParenExpr(Node* value, int line, int column)
      : Node(line, column), value_(value) {}
  Node* value() const { return value_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
};

class AtomExpr final : public Node {
 public:
  explicit AtomExpr(Node* value, int line, int column)
      : Node(line, column), value_(value) {}
  Node* value() const { return value_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
};

class Var final : public Node {
 public:
  explicit Var(std::string& name, int line, int column)
      : Node(line, column), name_(std::move(name)) {}
  const std::string& name() const { return name_; }
  void accept(Visitor& visitor) override;

 private:
  std::string name_;
};

}  // namespace php::ast
