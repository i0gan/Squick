set(ProjectName "core_plugin_config")
file(GLOB core_plugin_config_cc
	*.cc)

file(GLOB core_plugin_config_h
	*.h)
add_library(core_plugin_config SHARED ${core_plugin_config_cc} ${core_plugin_config_h})

set_target_properties( core_plugin_config PROPERTIES OUTPUT_NAME "config")
set_target_properties( core_plugin_config PROPERTIES PREFIX "")
set_target_properties( core_plugin_config PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )