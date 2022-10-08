set(ProjectName "plugin_server_world_client")
file(GLOB plugin_server_world_client_cc
	*.cc)

file(GLOB plugin_server_world_client_h 
	*.h)

add_library(plugin_server_world_client SHARED
	${plugin_server_world_client_cc}
	${plugin_server_world_client_h})
	
set_target_properties( plugin_server_world_client PROPERTIES OUTPUT_NAME "client")
set_target_properties( plugin_server_world_client PROPERTIES PREFIX "")
set_target_properties( plugin_server_world_client PROPERTIES 
	FOLDER "server/plugin/world_net_client"
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/world
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/world
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/world )

add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)
