set(ProjectName "plugin_server_world_pvp")
file(GLOB plugin_server_world_pvp_cc
	*.cc)

file(GLOB plugin_server_world_pvp_h 
	*.h)

add_library(plugin_server_world_pvp SHARED
	${plugin_server_world_pvp_cc}
	${plugin_server_world_pvp_h})
	
set_target_properties( plugin_server_world_pvp PROPERTIES OUTPUT_NAME "pvp")
set_target_properties( plugin_server_world_pvp PROPERTIES PREFIX "")
set_target_properties( plugin_server_world_pvp PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/world
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/world
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/world )

add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)
