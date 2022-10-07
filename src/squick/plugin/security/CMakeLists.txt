set(ProjectName "core_plugin_security")
file(GLOB core_plugin_security_cc
	*.cc)
	
file(GLOB core_plugin_security_h 
	*.h)

add_library(core_plugin_security SHARED
	${core_plugin_security_cc}
	${core_plugin_security_h})
	
set_target_properties( core_plugin_security PROPERTIES OUTPUT_NAME "security")
set_target_properties( core_plugin_security PROPERTIES PREFIX "")
set_target_properties( core_plugin_security PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )
add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)

