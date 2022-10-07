set(ProjectName "plugin_extend_db_logic")
file(GLOB plugin_extend_db_logic_cc
	*.cc)

file(GLOB plugin_extend_db_logic_h 
	*.h)

add_library(plugin_extend_db_logic SHARED
	${plugin_extend_db_logic_cc}
	${plugin_extend_db_logic_h})
	
set_target_properties( plugin_extend_db_logic PROPERTIES OUTPUT_NAME "logic")
set_target_properties( plugin_extend_db_logic PROPERTIES PREFIX "")
set_target_properties( plugin_extend_db_logic PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/db )
	
add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
	