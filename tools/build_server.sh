#! /bin/bash
# Author: i0gan
# Email : l418894113@gmail.com
# Date  : 2022-12-03
# Github: https://github.com/i0gan/Squick
# Description: Build all server plugins

source source/build.sh

# 将Proto文件生成代码
cd ${project_path}/tools
bash ./proto2code.sh

# 生成配置文件
cd ${project_path}/tools/
bash ./generate_config.sh

build_server() {
	cd ${project_path}
	mkdir -p "${build_path}/server"
	cd "${build_path}/server"
	cmake ${project_path}/src/server -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=$build_version
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
time build_server $@