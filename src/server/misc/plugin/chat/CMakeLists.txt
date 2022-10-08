set(ProjectName "plugin_server_misc_chat")
file(GLOB plugin_server_misc_chat_cc
	*.cc)
	
file(GLOB plugin_server_misc_chat_h 
	*.h)

add_library(plugin_server_misc_chat SHARED
	${plugin_server_misc_chat_cc}
	${plugin_server_misc_chat_h})
	
set_target_properties( plugin_server_misc_chat PROPERTIES OUTPUT_NAME "chat")
set_target_properties( plugin_server_misc_chat PROPERTIES PREFIX "")
set_target_properties( plugin_server_misc_chat PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/misc
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/misc
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/misc )

add_definitions(-D_X64 -D_CONSOLE)
