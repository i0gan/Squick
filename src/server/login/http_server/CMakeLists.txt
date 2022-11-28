set(ProjectName "plugin_server_login_http_server")
file(GLOB plugin_server_login_http_server_cc *.cc)
file(GLOB plugin_server_login_http_server_h *.h)

add_library(plugin_server_login_http_server SHARED
	${plugin_server_login_http_server_cc}
	${plugin_server_login_http_server_h}
)


set_target_properties( plugin_server_login_http_server PROPERTIES OUTPUT_NAME "http_server")
set_target_properties( plugin_server_login_http_server PROPERTIES PREFIX "")
set_target_properties( plugin_server_login_http_server PROPERTIES 
ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/login
RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/login
LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/login )


add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
