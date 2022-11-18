set(ProjectName "plugin_server_admin_server")
file(GLOB plugin_server_admin_server_cc
	*.cc)

file(GLOB plugin_server_admin_server_h 
	*.h)

add_library(plugin_server_admin_server SHARED
	${plugin_server_admin_server_cc}
	${plugin_server_admin_server_h}
)

set_target_properties( plugin_server_admin_server PROPERTIES OUTPUT_NAME "client")
set_target_properties( plugin_server_admin_server PROPERTIES PREFIX "")
set_target_properties( plugin_server_admin_server PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/admin
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/admin
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/admin )

add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)
