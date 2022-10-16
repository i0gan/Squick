#! /bin/bash
# build script for squick
# 2022-09-25
# i0gan

BuildPath="cache"
ProjectPath=`pwd`
Version="debug"
project_path=`pwd`

# 将Proto文件生成代码ll
cd src/squick/struct
bash ./gen_code.sh

cd ${ProjectPath}
# 编译工具
if test -f ./deploy/config/tools/config_generator ;then
    echo "配置文件生成工具已编译"
else
	cd ${ProjectPath}
	mkdir -p "${BuildPath}/tools"
	cd "${BuildPath}/tools"
	cmake ${ProjectPath} -G "CodeBlocks - Unix Makefiles" -DBUILD_TOOLS_ONLY=ON -DCMAKE_BUILD_TYPE=$Version
	make -j $(nproc)
fi

# 生成配置文件
cd ${ProjectPath}/deploy/config/tools/
bash ./gen_config.sh #> ${ProjectPath}/cache/gen_config.log

build_server() {
	cd ${ProjectPath}
	mkdir -p "${BuildPath}/server"
	cd "${BuildPath}/server"
	cmake ${ProjectPath} -G "CodeBlocks - Unix Makefiles" -DBUILD_MID_WARE_SDK=OFF -DCMAKE_BUILD_TYPE=$Version
	if [ $# -gt 0 ]; then
		# Compile all
		echo "Compile $@"
		make $@ -j $(nproc)

	else
		echo "Compile all"
		make -j $(nproc)
	fi

	cd ../
}

# build
time build_server $@


echo "Copying third_paty lib"
cd $project_path
cp third_party/build/lib/libprotobuf.so ./deploy/bin/lib/libprotobuf.so.32

