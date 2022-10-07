set(ProjectName "plugin_extend_db_client")
file(GLOB plugin_extend_db_client_cc
	*.cc)

file(GLOB plugin_extend_db_client_h 
	*.h)

add_library(plugin_extend_db_client SHARED
	${plugin_extend_db_client_cc}
	${plugin_extend_db_client_h})
	
set_target_properties( plugin_extend_db_client PROPERTIES OUTPUT_NAME "client")
set_target_properties( plugin_extend_db_client PROPERTIES PREFIX "")
set_target_properties( plugin_extend_db_client PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db )

add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)