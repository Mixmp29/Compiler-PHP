# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/mix/education/sem_7/LLVM/llvm/lab-1/build/debug/_deps/googletest-src"
  "/home/mix/education/sem_7/LLVM/llvm/lab-1/build/debug/_deps/googletest-build"
  "/home/mix/education/sem_7/LLVM/llvm/lab-1/build/debug/external/googletest"
  "/home/mix/education/sem_7/LLVM/llvm/lab-1/build/debug/external/googletest/tmp"
  "/home/mix/education/sem_7/LLVM/llvm/lab-1/build/debug/external/googletest/src/googletest-populate-stamp"
  "/home/mix/education/sem_7/LLVM/llvm/lab-1/build/debug/external/googletest/src"
  "/home/mix/education/sem_7/LLVM/llvm/lab-1/build/debug/external/googletest/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/mix/education/sem_7/LLVM/llvm/lab-1/build/debug/external/googletest/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/mix/education/sem_7/LLVM/llvm/lab-1/build/debug/external/googletest/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
