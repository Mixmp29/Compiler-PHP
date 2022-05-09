add_subdirectory(grammar)

set(test_name libphp_test)

add_executable(${test_name})

add_test(NAME ${test_name} COMMAND ${test_name})

json_target_set_compile_options(${test_name})

target_sources(
  ${test_name}
  PRIVATE
    test/lexer.cpp
)

target_link_libraries(
  ${test_name}
  PRIVATE
    ${lib_name}
    gtest
    gtest_main
)
