#!/bin/bash
rm -rf ./build
find . -name "*.o" | xargs  rm -rf
rm -rf ./lua-5.3.6/src/lua
rm -rf ./lua-5.3.6/src/luac
rm -rf ./lua-5.3.6/src/liblua.so
rm -rf ./lua-5.3.6/src/liblua.a
