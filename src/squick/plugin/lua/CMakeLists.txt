set(ProjectName "core_lua")
file(GLOB soruces *.cc)
file(GLOB headers *.h)
add_library(${ProjectName} SHARED ${soruces} ${headers})

if (APPLE)
	
elseif(UNIX)
	target_link_libraries(${ProjectName} liblua.a libprotobuf.so)
else()
	target_link_libraries(${ProjectName} lua.lib libprotobufd.dll)
endif()

LinkSquick(${ProjectName})
SquickOut(${ProjectName} "squick/plugin" ${SQUICK_BUILD_PLUGIN_CORE_PATH} "lua")