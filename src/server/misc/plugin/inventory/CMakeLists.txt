set(ProjectName "plugin_server_misc_inventory")
file(GLOB plugin_server_misc_inventory_cc
	*.cc)
	
file(GLOB plugin_server_misc_inventory_h 
	*.h)

add_library(plugin_server_misc_inventory SHARED
	${plugin_server_misc_inventory_cc}
	${plugin_server_misc_inventory_h})
	
set_target_properties( plugin_server_misc_inventory PROPERTIES OUTPUT_NAME "inventory")
set_target_properties( plugin_server_misc_inventory PROPERTIES PREFIX "")
set_target_properties( plugin_server_misc_inventory PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/misc
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/misc
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/misc )

add_definitions(-D_X64 -D_CONSOLE)
