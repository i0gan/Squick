cmake_minimum_required(VERSION 2.8)

set_property(GLOBAL PROPERTY USE_FOLDERS On)
project(Squick)
set(SolutionDir ${PROJECT_SOURCE_DIR}/..)
message(STATUS "SolutionDir=" ${SolutionDir})

# 可执行文件生成路径
set(SQUICK_BUILD_EXE_PATH ${PROJECT_SOURCE_DIR}/bin)
# 可执行文件运行依赖动态链接库存放路径
set(SQUICK_RUNTIME_LIB_PATH ${PROJECT_SOURCE_DIR}/bin/lib)
# 核心插件路径
set(SQUICK_BUILD_PLUGIN_CORE_PATH ${PROJECT_SOURCE_DIR}/bin/plugin/core)
# 服务器插件路径
set(SQUICK_BUILD_PLUGIN_SERVER_PATH ${PROJECT_SOURCE_DIR}/bin/plugin/server)
# 拓展插件路径
set(SQUICK_BUILD_PLUGIN_EXTEND_PATH ${PROJECT_SOURCE_DIR}/bin/plugin/extend)
# 测试插件路径
set(SQUICK_BUILD_PLUGIN_TESTER_PATH ${PROJECT_SOURCE_DIR}/bin/plugin/tester)


include_directories(
	${SolutionDir}
	${SolutionDir}/src/
	${SolutionDir}/third_party/
	${SolutionDir}/third_party/build/include
	${SolutionDir}/third_party/zlib
	)

message("Build Type:"${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})

if( CMAKE_BUILD_TYPE STREQUAL "debug" )
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17  -g -ggdb -DDEBUG -fPIC -Wendif-labels") # -O0 -Wall
else()
	set(CMAKE_BUILD_TYPE "release")
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -O3 -fPIC -std=c++17  -Wendif-labels")# 
	
endif()

set(LDFLAGS "$ENV{LDFLAGS} -stdlib=libc++")
#add_definitions(-std=c++17)


if( CMAKE_BUILD_TYPE STREQUAL "debug" )
	set(ThirdPartyLibPath ${SolutionDir}/third_party/build/lib ${SolutionDir}/build/debug/lib )
else()
	set(ThirdPartyLibPath ${SolutionDir}/third_party/build/lib ${SolutionDir}/build/release/lib)
endif()


link_directories(${ThirdPartyLibPath})

add_definitions(-D_X64 -D_CONSOLE -DSQUICK_DYNAMIC_PLUGIN )
message("Build Squicks")
add_subdirectory(squick)
add_subdirectory(server)
#add_subdirectory(src/tester)
#add_subdirectory(src/tutorial)