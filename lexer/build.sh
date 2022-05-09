#!/bin/bash

readonly antlr=antlr-4.10.1-complete.jar

cmake --preset debug
cmake --build --preset debug
ctest --preset debug
