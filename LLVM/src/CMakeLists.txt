set(test_name graph)
set(vec_name Graph)

add_executable(
    ${test_name}
)

target_sources(
  ${test_name}
  PRIVATE
    ${test_name}/Graph.cpp
)

add_library(
  ${vec_name} INTERFACE
  graph/Graph.hpp
)

include(CompileOptions)

set_compile_options(${test_name})

target_include_directories(
  ${vec_name}
  INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
  ${test_name}
  PRIVATE
    ${llvm_libs}
    Graph
)

set_target_properties(
${test_name} 
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)