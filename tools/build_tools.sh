#! /bin/bash
# Author: i0gan
# Email: l418894113@gmail.com
# Date: 2022-11-27
# Github: https://github.com/i0gan/Squick
# Description: build script for squick

build_version="release"
project_path=`pwd`/..
build_path="$project_path/cache"

# 编译工具
cd ${project_path}
mkdir -p "${build_path}/tools"
cd "${build_path}/tools"
cmake ${project_path}/src/tools/xlsx2need 
make -j $(nproc)
cp ${build_path}/tools/xlsx2need ${project_path}/tools