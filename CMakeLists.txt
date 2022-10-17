cmake_minimum_required(VERSION 2.8)

set_property(GLOBAL PROPERTY USE_FOLDERS On)

option(BUILD_TOOLS_ONLY "help string describing option" OFF)
macro(linkSDK projName)
	add_dependencies(${projName} core struct net_plugin)
	target_link_libraries(${projName} core struct net_plugin)
endmacro(linkSDK)

project(Squick)

set(SolutionDir ${PROJECT_SOURCE_DIR})


# 可执行文件生成路径
set(SQUICK_BUILD_EXE_PATH ${PROJECT_SOURCE_DIR}/deploy/bin)
# 可执行文件运行依赖动态链接库存放路径
set(SQUICK_RUNTIME_LIB_PATH ${PROJECT_SOURCE_DIR}/deploy/bin/lib)
# 核心插件路径
set(SQUICK_BUILD_PLUGIN_CORE_PATH ${PROJECT_SOURCE_DIR}/deploy/bin/plugin/core)
# 服务器插件路径
set(SQUICK_BUILD_PLUGIN_SERVER_PATH ${PROJECT_SOURCE_DIR}/deploy/bin/plugin/server)
# 拓展插件路径
set(SQUICK_BUILD_PLUGIN_EXTEND_PATH ${PROJECT_SOURCE_DIR}/deploy/bin/plugin/extend)


message(STATUS "SolutionDir=" ${SolutionDir})

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

if(${BUILD_TOOLS_ONLY} STREQUAL "ON")
	message("Build Tools Only")
	add_subdirectory(src/tools)
else()
	add_definitions(-D_X64 -D_CONSOLE -DSQUICK_DYNAMIC_PLUGIN )
	message("Build Squicks")
	add_subdirectory(src/squick)
	add_subdirectory(src/server)
	#add_subdirectory(src/tutorial)
endif()
