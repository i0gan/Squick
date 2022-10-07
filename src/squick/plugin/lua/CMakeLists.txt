set(ProjectName "core_plugin_lua")
file(GLOB core_plugin_lua_cc *.cc)
file(GLOB core_plugin_lua_h *.h)

add_library(core_plugin_lua SHARED
	${core_plugin_lua_cc}
	${core_plugin_lua_h})

target_link_libraries(core_plugin_lua liblua.a libprotobuf.so)
add_dependencies(core_plugin_lua squick_struct)

set_target_properties( core_plugin_lua PROPERTIES OUTPUT_NAME "lua")
set_target_properties( core_plugin_lua PROPERTIES PREFIX "")
set_target_properties( core_plugin_lua PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )