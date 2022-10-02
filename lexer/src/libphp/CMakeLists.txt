set(target_name php)

add_library(${target_name} STATIC)

include(CompileOptions)
json_target_set_compile_options(${target_name})

target_sources(
  ${target_name}
  PUBLIC
    libphp/ast/Ast.hpp
    libphp/ast/Visitor.hpp
    libphp/ast/XmlSerializer.hpp
    libphp/ast/SymTableVisitor.hpp
    libphp/ast/Symbol.hpp
    libphp/dump_tokens.hpp
    libphp/dump_symtable.hpp
    libphp/parser.hpp
  PRIVATE
    libphp/ast/detail/Builder.cpp
    libphp/ast/detail/Builder.hpp
    libphp/ast/Ast.cpp
    libphp/ast/XmlSerializer.cpp
    libphp/ast/SymTableVisitor.cpp
    libphp/dump_tokens.cpp
    libphp/dump_symtable.cpp
    libphp/parser.cpp
)

target_include_directories(
  ${target_name} 
  PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
  ${target_name}
  PRIVATE
    Php
    fmt
    pugixml
)

set(test_name libphp_test)

add_executable(${test_name})

add_test(NAME ${test_name} COMMAND ${test_name})

json_target_set_compile_options(${test_name})

target_sources(
  ${test_name}
  PRIVATE
    test/lexer.cpp
    test/parser.cpp
    test/symtable.cpp
)

target_link_libraries(
  ${test_name}
  PRIVATE
    ${target_name}
    Php
    php
    gtest
    gtest_main
)
