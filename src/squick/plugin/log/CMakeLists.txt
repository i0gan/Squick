set(ProjectName "core_plugin_log")
file(GLOB core_plugin_log_cc *.cc)
file(GLOB core_plugin_log_h *.h)

add_library(core_plugin_log SHARED
	${core_plugin_log_cc}
	${core_plugin_log_h})

set_target_properties( core_plugin_log PROPERTIES OUTPUT_NAME "log")
set_target_properties( core_plugin_log PROPERTIES PREFIX "")
set_target_properties( core_plugin_log PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )