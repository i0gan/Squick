set(ProjectName "plugin_server_misc_consume_manager")
file(GLOB plugin_server_misc_consume_manager_cc
	*.cc)
	
file(GLOB plugin_server_misc_consume_manager_h 
	*.h)

add_library(plugin_server_misc_consume_manager SHARED
	${plugin_server_misc_consume_manager_cc}
	${plugin_server_misc_consume_manager_h})
	
set_target_properties( plugin_server_misc_consume_manager PROPERTIES OUTPUT_NAME "consume_manager")
set_target_properties( plugin_server_misc_consume_manager PROPERTIES PREFIX "")
set_target_properties( plugin_server_misc_consume_manager PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/misc
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/misc
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/misc )

add_definitions(-D_X64 -D_CONSOLE)
