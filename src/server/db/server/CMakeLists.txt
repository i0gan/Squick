set(ProjectName "plugin_server_db_server")
file(GLOB plugin_server_db_server_cc
	*.cc)

file(GLOB plugin_server_db_server_h 
	*.h)

add_library(plugin_server_db_server SHARED
	${plugin_server_db_server_cc}
	${plugin_server_db_server_h}
)

set_target_properties( plugin_server_db_server PROPERTIES OUTPUT_NAME "server")
set_target_properties( plugin_server_db_server PROPERTIES PREFIX "")
set_target_properties( plugin_server_db_server PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/db
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/db
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/db )

add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
