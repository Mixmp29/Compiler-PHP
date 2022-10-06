#include <libphp/ast/CodeGen.hpp>

#include <string>

namespace php::ast {

void CodeGen::exec(Document& document, SymTable& symtable, std::ostream& out) {
  CodeGen codegen(symtable, out);

  out << "target triple = \"x86_64-pc-linux-gnu\"\n"
      << "\n";

  document.get_node()->accept(codegen);

  out << "\n";

  codegen.generate();
}

void CodeGen::generate() {
  if (generate_flags_.print_string || generate_flags_.read_string) {
    out_ << "@format.str = constant [4 x i8] c\"%s\\0A\\00\"\n"
         << "\n";
  }
  if (generate_flags_.print_int) {
    out_ << "@format.pint = constant [4 x i8] c\"%d\\0A\\00\"\n"
         << "\n";
  }
  if (generate_flags_.read_int) {
    out_ << "@format.rint = constant [3 x i8] c\"%d\\00\"\n"
         << "\n";
  }
  if (generate_flags_.string) {
    out_ << "declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture "
            "writeonly, i8* noalias nocapture readonly, i64, i1 immarg)\n"
         << "\n";
  }
  if (generate_flags_.print_string || generate_flags_.print_int) {
    out_ << "declare i32 @printf(i8* %format, ...)\n"
         << "\n";
  }
  if (generate_flags_.read_string || generate_flags_.read_int) {
    out_ << "declare i32 @__isoc99_scanf(i8*, ...)\n"
         << "\n";
  }
  if (generate_flags_.print_int) {
    out_ << "define void @print_int(i32 %x) {\n"
         << "  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8],"
            "[4 x i8]* @format.pint, i64 0, i64 0), i32 %x)\n"
         << "  ret void\n"
         << "}\n"
         << "\n";
  }
  if (generate_flags_.print_string) {
    out_ << "define void @print_string(i8* %x) {\n"
            "  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 "
            "x "
            "i8]* @format.str, i64 0, i64 0), i8* %x)\n"
            "  ret void\n"
         << "}\n"
         << "\n";
  }
  if (generate_flags_.read_int) {
    out_ << "define void @read_int(i32* %x) {\n"
         << "  call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr "
            "([3 x i8], [3 x i8]* @format.rint, i64 0, i64 0), i32* %x)\n"
         << "  ret void\n"
         << "}\n"
         << "\n";
  }

  out_ << "define i32 @main() #0{\n"
       << body_.str() << "  ret i32 0\n"
       << "}\n"
       << "\n"
       << "attributes #0 = { \"frame-pointer\"=\"all\" }\n";
}

void CodeGen::visit(Elements& value) {
  for (const auto& element : value.value()) {
    element->accept(*this);
  }
}

void CodeGen::visit(Statement& value) {
  value.value()->accept(*this);
}

void CodeGen::visit(ElementWithColon& value) {
  value.value()->accept(*this);
}

void CodeGen::visit(Echo& value) {
  value.value()->accept(*this);
  if (states_.string) {
    generate_flags_.print_string = true;
    body_ << "  call void @print_string(i8* %t" << pop_value() << ")\n";
    states_.string = false;
  } else {
    generate_flags_.print_int = true;
    body_ << "  call void @print_int(i32 %t" << pop_value() << ")\n";
  }
}

void CodeGen::visit(Print& value) {
  value.value()->accept(*this);
  if (states_.string) {
    generate_flags_.print_string = true;
    body_ << "  call void @print_string(i8* %t" << pop_value() << ")\n";
    states_.string = false;
  } else {
    generate_flags_.print_int = true;
    body_ << "  call void @print_int(i32 %t" << pop_value() << ")\n";
  }
}

void CodeGen::visit(Input& /*value*/) {
  generate_flags_.read_int = true;
  var_num_++;
  body_ << "  %t" << var_num_ << " = alloca i32, align 4\n"
        << "  call void @read_int(i32* %t" << var_num_ << ")\n";
  push_value(var_num_);
}

void CodeGen::visit(IfElse& value) {
  states_.ifelse = true;

  value.ifState()->accept(*this);
  value.elseState()->accept(*this);

  body_ << "  br label %t" << else_label_ << "\n"
        << "\n"
        << "t" << else_label_ << ":\n";

  states_.ifelse = false;
}

void CodeGen::visit(IfState& value) {
  value.comparison()->accept(*this);

  int label = var_num_ += 2;
  if (states_.ifelse) {
    else_label_ = ++var_num_;
  }
  body_ << "  br i1 %t" << pop_value() << ", label %t" << label - 1
        << ", label %t" << label << "\n"
        << "\n"
        << "t" << label - 1 << ":\n";

  value.codeBlock()->accept(*this);

  body_ << "  br label %t";
  if (states_.ifelse) {
    body_ << label + 1;
  } else {
    body_ << label;
  }
  body_ << "\n"
        << "\n"
        << "t" << label << ":\n";
}

void CodeGen::visit(ElseState& value) {
  value.codeBlock()->accept(*this);
}

void CodeGen::visit(WhileState& value) {
  int label = var_num_ += 3;
  body_ << "  br label %t" << label - 2 << "\n"
        << "\n"
        << "t" << label - 2 << ":\n";

  value.comparison()->accept(*this);

  body_ << "  br i1 %t" << pop_value() << ", label %t" << label - 1
        << ", label %t" << label << "\n"
        << "\n"
        << "t" << label - 1 << ":\n";

  value.codeBlock()->accept(*this);

  body_ << "  br label %t" << label - 2 << "\n"
        << "\n"
        << "t" << label << ":\n";
}

void CodeGen::visit(Assigned& value) {
  value.var()->accept(*this);
  value.val()->accept(*this);
  if (states_.string) {
    generate_flags_.string = true;

    int value = pop_value();

    body_ << "  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %t"
          << pop_value() << ", i8* align 1 %t" << value
          << ", i64 256, i1 false)\n";
    states_.string = false;
  } else {
    body_ << "  store i32 %t" << pop_value() << ", i32* %t" << pop_value()
          << "\n";
  }
}

void CodeGen::visit(CodeBlock& value) {
  value.elements()->accept(*this);
}

void CodeGen::visit(OpExpr& value) {
  value.rhs()->accept(*this);
  value.lhs()->accept(*this);

  var_num_++;

  body_ << "  %t" << var_num_ << " = ";

  if (value.op() == "+") {
    body_ << "add nsw";
  }
  if (value.op() == "-") {
    body_ << "sub nsw";
  }
  if (value.op() == "*") {
    body_ << "mul nsw";
  }
  if (value.op() == "/") {
    body_ << "sdiv";
  }
  if (value.op() == "%") {
    body_ << "srem";
  }

  body_ << " i32 %t" << pop_value() << ", %t" << pop_value() << "\n";
  push_value(var_num_);
}

void CodeGen::visit(StrExpr& value) {
  value.lhs()->accept(*this);
  value.rhs()->accept(*this);
}

void CodeGen::visit(UPostExpr& value) {
  value.value()->accept(*this);
}

void CodeGen::visit(UPrefExpr& value) {
  value.value()->accept(*this);
}

void CodeGen::visit(ParenExpr& value) {
  value.value()->accept(*this);
}

void CodeGen::visit(AtomExpr& value) {
  value.value()->accept(*this);

  if (!states_.string) {
    var_num_++;
    body_ << "  %t" << var_num_ << " = load i32, i32* %t" << pop_value()
          << "\n";
    push_value(var_num_);
  }
}

void CodeGen::visit(Comparison& value) {
  value.rhs()->accept(*this);
  value.lhs()->accept(*this);
  value.op()->accept(*this);
}

void CodeGen::visit(Var& value) {
  states_.var = true;
  value.value()->accept(*this);
  states_.var = false;
}

void CodeGen::visit(Condition& value) {
  var_num_++;

  body_ << "  %t" << var_num_ << " = icmp ";

  if (value.comp() == "==") {
    body_ << "eq";
  }
  if (value.comp() == "!=") {
    body_ << "ne";
  }
  if (value.comp() == ">") {
    body_ << "sgt";
  }
  if (value.comp() == "<") {
    body_ << "slt";
  }
  if (value.comp() == ">=") {
    body_ << "sge";
  }
  if (value.comp() == "<=") {
    body_ << "sle";
  }

  body_ << " i32 %t" << pop_value() << ", %t" << pop_value() << "\n";
  push_value(var_num_);
}

void CodeGen::visit(Id& value) {
  states_.string =
      (symtable_.at(value.name()).get_type() == Symbol::Type::String);

  auto it = ids_.find(value.name());

  if (states_.string) {
    if (it == ids_.end()) {
      var_num_++;

      ids_.insert({value.name(), var_num_});

      body_ << "  %t" << var_num_ << " = alloca [256 x i8], align 16\n";
    }
    var_num_++;
    body_ << "  %t" << var_num_
          << " = getelementptr inbounds [256 x i8], [256 x i8]* %t"
          << ids_[value.name()] << ", i64 0, i64 0\n";
    push_value(var_num_);
  } else {
    if (it == ids_.end()) {
      var_num_++;

      ids_.insert({value.name(), var_num_});

      body_ << "  %t" << var_num_ << " = alloca i32, align 4\n";
      if (!states_.var) {
        body_ << "  store i32 0, i32* %t" << var_num_ << "\n";
      }
      push_value(var_num_);
    } else {
      push_value(it->second);
    }
  }
}

void CodeGen::visit(Value& value) {
  var_num_++;
  body_ << "  %t" << var_num_ << " = alloca i32, align 4\n"
        << "  store i32 " << value.integer() << ", i32* %t" << var_num_ << "\n";

  push_value(var_num_);
}

void CodeGen::visit(Str& value) {
  states_.string = true;
  var_num_++;
  out_ << "@str" << var_num_ << " = constant [" << value.text().size() - 1
       << " x i8] c" << value.text().substr(0, value.text().size() - 1)
       << "\\00\"\n";
  body_ << "  %t" << var_num_ << " = getelementptr inbounds ["
        << value.text().size() - 1 << " x i8], [" << value.text().size() - 1
        << " x i8]* @str" << var_num_ << ", i64 0, i64 0\n";
  push_value(var_num_);
}

int CodeGen::pop_value() {
  int res = values_.top();
  values_.pop();
  return res;
}

void CodeGen::push_value(int val) {
  values_.push(val);
}

}  // namespace php::ast
