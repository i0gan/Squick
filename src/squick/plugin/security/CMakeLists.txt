set(ProjectName "plugin_core_security")
file(GLOB plugin_core_security_cc
	*.cc)
	
file(GLOB plugin_core_security_h 
	*.h)

add_library(plugin_core_security SHARED
	${plugin_core_security_cc}
	${plugin_core_security_h})
	
set_target_properties( plugin_core_security PROPERTIES OUTPUT_NAME "security")
set_target_properties( plugin_core_security PROPERTIES PREFIX "")
set_target_properties( plugin_core_security PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH} )
add_definitions(
	-DELPP_NO_DEFAULT_LOG_FILE
)

