set(ProjectName "plugin_extend_db_server")
file(GLOB plugin_extend_db_server_cc
	*.cc)

file(GLOB plugin_extend_db_server_h 
	*.h)

add_library(plugin_extend_db_server SHARED
	${plugin_extend_db_server_cc}
	${plugin_extend_db_server_h})
	
set_target_properties( plugin_extend_db_server PROPERTIES OUTPUT_NAME "server")
set_target_properties( plugin_extend_db_server PROPERTIES PREFIX "")
set_target_properties( plugin_extend_db_server PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db )

add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
