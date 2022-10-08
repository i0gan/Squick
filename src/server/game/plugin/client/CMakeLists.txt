set(ProjectName "plugin_server_game_client")
file(GLOB plugin_server_game_client_cc
	*.cc)
	
file(GLOB plugin_server_game_client_h 
	*.h)

add_library(plugin_server_game_client SHARED
	${plugin_server_game_client_cc}
	${plugin_server_game_client_h}
)

set_target_properties( plugin_server_game_client PROPERTIES OUTPUT_NAME "client")
set_target_properties( plugin_server_game_client PROPERTIES PREFIX "")
set_target_properties( plugin_server_game_client PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/game
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/game
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/game )

add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
