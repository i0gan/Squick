set(ProjectName "plugin_core_log")
file(GLOB plugin_core_log_cc *.cc)
file(GLOB plugin_core_log_h *.h)

add_library(plugin_core_log SHARED
	${plugin_core_log_cc}
	${plugin_core_log_h})

set_target_properties( plugin_core_log PROPERTIES OUTPUT_NAME "log")
set_target_properties( plugin_core_log PROPERTIES PREFIX "")
set_target_properties( plugin_core_log PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH} )