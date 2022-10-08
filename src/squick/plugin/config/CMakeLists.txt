set(ProjectName "plugin_core_config")
file(GLOB plugin_core_config_cc
	*.cc)

file(GLOB plugin_core_config_h
	*.h)
add_library(plugin_core_config SHARED ${plugin_core_config_cc} ${plugin_core_config_h})

set_target_properties( plugin_core_config PROPERTIES OUTPUT_NAME "config")
set_target_properties( plugin_core_config PROPERTIES PREFIX "")
set_target_properties( plugin_core_config PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH} )