set(ProjectName "kernel")

file(GLOB plugin_core_kernel_cc *.cc)
file(GLOB plugin_core_kernel_h *.h)

add_library(plugin_core_kernel SHARED
	${plugin_core_kernel_cc}
	${plugin_core_kernel_h})

set_target_properties( plugin_core_kernel PROPERTIES OUTPUT_NAME "kernel")
set_target_properties( plugin_core_kernel PROPERTIES PREFIX "")
set_target_properties( plugin_core_kernel PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH} )

