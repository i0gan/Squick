set(ProjectName "plugin_core_navigation")
file(GLOB plugin_core_navigation_cc *.cc)
file(GLOB plugin_core_navigation_h *.h)
	
add_library(plugin_core_navigation SHARED
	${plugin_core_navigation_cc}
	${plugin_core_navigation_h})

target_include_directories(plugin_core_navigation PUBLIC
	${SolutionDir}/third_party/navigation/)

target_link_libraries(plugin_core_navigation recastnavigation)
target_link_libraries(plugin_core_navigation -static-libstdc++)

set_target_properties( plugin_core_navigation PROPERTIES OUTPUT_NAME "navigation")
set_target_properties( plugin_core_navigation PROPERTIES PREFIX "")
set_target_properties( plugin_core_navigation PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH} )