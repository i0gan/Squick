set(ProjectName "core_plugin_net")

file(GLOB core_plugin_net_cc *.cc)
file(GLOB core_plugin_net_h *.h)

add_library(core_plugin_net SHARED ${core_plugin_net_cc} ${core_plugin_net_h})

add_definitions(-DSQUICK_NONCLIENT_BUILD)
set_target_properties( core_plugin_net PROPERTIES OUTPUT_NAME "net")
set_target_properties( core_plugin_net PROPERTIES PREFIX "")
set_target_properties( core_plugin_net PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH})
	
target_link_libraries(core_plugin_net libevent.a)
target_link_libraries(core_plugin_net libevent_core.a)
target_link_libraries(core_plugin_net libevent_extra.a)
#target_link_libraries(core_plugin_net libevent_openssl.a)
#target_link_libraries(core_plugin_net libssl.a)
#target_link_libraries(core_plugin_net libcrypto.a)
target_link_libraries(core_plugin_net squick_struct)
target_link_libraries(core_plugin_net -static-libstdc++)
add_definitions(
	-D_THREAD_SAFE
)
