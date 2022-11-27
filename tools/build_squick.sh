#! /bin/bash
# Author: i0gan
# Email: i0gan@pwnsky.com
# Date: 2022-09-25
# Github: https://github.com/i0gan/Squick
# Description: build script for squick

build_version="release"
project_path=`pwd`/..
build_path="$project_path/cache"
# 将Proto文件生成代码
cd ${project_path}/tools
bash ./proto2code.sh

# 生成配置文件
cd ${project_path}/tools/
bash ./generate_config.sh

build_squick() {
	cd ${project_path}
	mkdir -p "${build_path}/squick"
	cd "${build_path}/squick"
	cmake ${project_path} -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=$build_version
	if [ $# -gt 0 ]; then
		# Compile all
		echo "Compile $@"
		make $@ -j $(nproc)
	else
		echo "Compile all"
		make -j $(nproc)
	fi
}


# build
time build_squick $@

# gen_deploy
echo "Copying third_paty lib"
cd $project_path
cp third_party/build/lib/libprotobuf.so ./bin/lib/libprotobuf.so.32
