set(ProjectName "plugin_core_actor")
file(GLOB plugin_core_actor_cc *.cc)
file(GLOB plugin_core_actor_h *.h)

add_library(plugin_core_actor SHARED
	${plugin_core_actor_cc}
	${plugin_core_actor_h})
	
set_target_properties( plugin_core_actor PROPERTIES OUTPUT_NAME "actor")
set_target_properties( plugin_core_actor PROPERTIES PREFIX "")
set_target_properties( plugin_core_actor PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH} )