set(ProjectName "core_plugin_navigation")
file(GLOB core_plugin_navigation_cc *.cc)
file(GLOB core_plugin_navigation_h *.h)
	
add_library(core_plugin_navigation SHARED
	${core_plugin_navigation_cc}
	${core_plugin_navigation_h})

target_include_directories(core_plugin_navigation PUBLIC
	${SolutionDir}/third_party/navigation/)

target_link_libraries(core_plugin_navigation tnavigation)
target_link_libraries(core_plugin_navigation -static-libstdc++)

set_target_properties( core_plugin_navigation PROPERTIES OUTPUT_NAME "navigation")
set_target_properties( core_plugin_navigation PROPERTIES PREFIX "")
set_target_properties( core_plugin_navigation PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )