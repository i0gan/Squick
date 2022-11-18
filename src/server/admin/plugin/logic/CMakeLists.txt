set(ProjectName "plugin_server_admin_logic")
file(GLOB plugin_server_admin_logic_cc
	*.cc)

file(GLOB plugin_server_admin_logic_h 
	*.h)

add_library(plugin_server_admin_logic SHARED
	${plugin_server_admin_logic_cc}
	${plugin_server_admin_logic_h}
)

set_target_properties( plugin_server_admin_logic PROPERTIES OUTPUT_NAME "client")
set_target_properties( plugin_server_admin_logic PROPERTIES PREFIX "")
set_target_properties( plugin_server_admin_logic PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/admin
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/admin
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/admin )

add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)
