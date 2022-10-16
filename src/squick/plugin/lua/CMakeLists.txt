set(ProjectName "plugin_core_lua")
file(GLOB plugin_core_lua_cc *.cc)
file(GLOB plugin_core_lua_h *.h)

add_library(plugin_core_lua SHARED
	${plugin_core_lua_cc}
	${plugin_core_lua_h})

target_link_libraries(plugin_core_lua liblua.a libprotobuf.so)
add_dependencies(plugin_core_lua squick_struct)

set_target_properties( plugin_core_lua PROPERTIES OUTPUT_NAME "lua")
set_target_properties( plugin_core_lua PROPERTIES PREFIX "")
set_target_properties( plugin_core_lua PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH} )