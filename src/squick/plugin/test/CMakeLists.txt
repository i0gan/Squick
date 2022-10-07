set(ProjectName "core_plugin_test")
file(GLOB core_plugin_test_cc
	*.cc)
	
file(GLOB core_plugin_test_h 
	*.h)

add_library(core_plugin_test SHARED
	${core_plugin_test_cc}
	${core_plugin_test_h})
	
set_target_properties( core_plugin_test PROPERTIES OUTPUT_NAME "test")
set_target_properties( core_plugin_test PROPERTIES PREFIX "")
set_target_properties( core_plugin_test PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )