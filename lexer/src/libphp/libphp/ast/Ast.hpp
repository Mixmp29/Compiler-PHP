#pragma once

#include <memory>
#include <vector>

namespace php::ast {

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
    nodes_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    return dynamic_cast<T*>(nodes_.back().get());
  }

  void set_value(ast::Node* node) { node_ = node; }
  ast::Node* get_node() const { return node_; }

 private:
  std::vector<std::unique_ptr<Node>> nodes_;
  ast::Node* node_ = nullptr;
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

class Input final : public Node {
 public:
  explicit Input(int line, int column) : Node(line, column) {}
  void accept(Visitor& visitor) override;

 private:
};

class IfElse final : public Node {
 public:
  explicit IfElse(Node* ifState, Node* elseState, int line, int column)
      : Node(line, column), ifState_(ifState), elseState_(elseState) {}
  Node* ifState() const { return ifState_; }
  Node* elseState() const { return elseState_; }
  void accept(Visitor& visitor) override;

 private:
  Node* ifState_;
  Node* elseState_;
};

class IfState final : public Node {
 public:
  explicit IfState(Node* comparison, Node* codeBlock, int line, int column)
      : Node(line, column), comparison_(comparison), codeBlock_(codeBlock) {}
  Node* comparison() const { return comparison_; }
  Node* codeBlock() const { return codeBlock_; }
  void accept(Visitor& visitor) override;

 private:
  Node* comparison_;
  Node* codeBlock_;
};

class ElseState final : public Node {
 public:
  explicit ElseState(Node* codeBlock, int line, int column)
      : Node(line, column), codeBlock_(codeBlock) {}
  Node* codeBlock() const { return codeBlock_; }
  void accept(Visitor& visitor) override;

 private:
  Node* codeBlock_;
};

class WhileState final : public Node {
 public:
  explicit WhileState(Node* comparison, Node* codeBlock, int line, int column)
      : Node(line, column), comparison_(comparison), codeBlock_(codeBlock) {}
  Node* comparison() const { return comparison_; }
  Node* codeBlock() const { return codeBlock_; }
  void accept(Visitor& visitor) override;

 private:
  Node* comparison_;
  Node* codeBlock_;
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
  explicit CodeBlock(Node* elements, int line, int column)
      : Node(line, column), elements_(elements) {}
  Node* elements() const { return elements_; }
  void accept(Visitor& visitor) override;

 private:
  Node* elements_;
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

class Comparison final : public Node {
 public:
  explicit Comparison(Node* lhs, Node* op, Node* rhs, int line, int column)
      : Node(line, column), lhs_(lhs), op_(op), rhs_(rhs) {}
  Node* lhs() const { return lhs_; }
  Node* op() const { return op_; }
  Node* rhs() const { return rhs_; }
  void accept(Visitor& visitor) override;

 private:
  Node* lhs_;
  Node* op_;
  Node* rhs_;
};

class Var final : public Node {
 public:
  explicit Var(Node* value, int line, int column)
      : Node(line, column), value_(value) {}
  Node* value() const { return value_; }
  void accept(Visitor& visitor) override;

 private:
  Node* value_;
};

class Condition final : public Node {
 public:
  explicit Condition(std::string& comp, int line, int column)
      : Node(line, column), comp_(std::move(comp)) {}
  const std::string& comp() const { return comp_; }
  void accept(Visitor& visitor) override;

 private:
  std::string comp_;
};

class Id final : public Node {
 public:
  explicit Id(std::string& name, int line, int column)
      : Node(line, column), name_(std::move(name)) {}
  const std::string& name() const { return name_; }
  void accept(Visitor& visitor) override;

 private:
  std::string name_;
};

class Value final : public Node {
 public:
  explicit Value(std::string integer, int line, int column)
      : Node(line, column), integer_(std::move(integer)) {}
  const std::string& integer() const { return integer_; }
  void accept(Visitor& visitor) override;

 private:
  std::string integer_;
};

class Str final : public Node {
 public:
  explicit Str(std::string& name, int line, int column)
      : Node(line, column), name_(std::move(name)) {}
  const std::string& text() const { return name_; }
  void accept(Visitor& visitor) override;

 private:
  std::string name_;
};

}  // namespace php::ast