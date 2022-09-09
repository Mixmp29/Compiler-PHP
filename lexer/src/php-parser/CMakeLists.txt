set(target_name php-parser)

add_executable(${target_name})

target_include_directories(${target_name} PRIVATE .)

include(CompileOptions)
json_target_set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
    ${target_name}/main.cpp
)

target_link_libraries(
  ${target_name}
  PRIVATE
    cxxopts
    php
    Php
    antlr4
)

set_target_properties(
  ${target_name}
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
