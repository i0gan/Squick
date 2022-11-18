#!/bin/bash
rm -rf ./build
find . -name "*.o" | xargs  rm -rf
rm -rf ./lua/src/lua
rm -rf ./lua/src/luac
rm -rf ./lua/src/liblua.so
rm -rf ./lua/src/liblua.a
