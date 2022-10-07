set(ProjectName "core_plugin_actor")
file(GLOB core_plugin_actor_cc *.cc)
file(GLOB core_plugin_actor_h *.h)

add_library(core_plugin_actor SHARED
	${core_plugin_actor_cc}
	${core_plugin_actor_h})
	
set_target_properties( core_plugin_actor PROPERTIES OUTPUT_NAME "actor")
set_target_properties( core_plugin_actor PROPERTIES PREFIX "")
set_target_properties( core_plugin_actor PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )