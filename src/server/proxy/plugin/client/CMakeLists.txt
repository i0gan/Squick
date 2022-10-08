set(ProjectName "plugin_server_proxy_client")
file(GLOB plugin_server_proxy_client_cc
	*.cc)

file(GLOB plugin_server_proxy_client_h 
	*.h)

add_library(plugin_server_proxy_client SHARED
	${plugin_server_proxy_client_cc}
	${plugin_server_proxy_client_h})
set_target_properties( plugin_server_proxy_client PROPERTIES OUTPUT_NAME "client")
set_target_properties( plugin_server_proxy_client PROPERTIES PREFIX "")
set_target_properties( plugin_server_proxy_client PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/proxy
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/proxy
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/proxy )

add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)
