set(ProjectName "kernel")

file(GLOB core_plugin_kernel_cc *.cc)
file(GLOB core_plugin_kernel_h *.h)

add_library(core_plugin_kernel SHARED
	${core_plugin_kernel_cc}
	${core_plugin_kernel_h})

set_target_properties( core_plugin_kernel PROPERTIES OUTPUT_NAME "kernel")
set_target_properties( core_plugin_kernel PROPERTIES PREFIX "")
set_target_properties( core_plugin_kernel PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )

