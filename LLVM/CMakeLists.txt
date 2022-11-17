cmake_minimum_required(VERSION 3.13)

project(
  smthllvm
  VERSION 0.1
  LANGUAGES CXX
)

list(
  APPEND
  CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/cmake
)

find_package(LLVM REQUIRED CONFIG)
find_package(ZLIB)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(llvm_libs support core irreader)


find_program(
  CLANG_TIDY_EXE
  NAMES clang-tidy-10 clang-tidy
)

if(NOT CLANG_TIDY_EXE)
  message(WARNING "clang-tidy not found")
else()
  execute_process(
    COMMAND ${CLANG_TIDY_EXE} --version
    OUTPUT_VARIABLE clang_tidy_version
  )
  message("clang-tidy version:\n${clang_tidy_version}")
endif()

add_subdirectory(src)
add_subdirectory(external)
