set(ProjectName "plugin_core_net")

file(GLOB plugin_core_net_cc *.cc)
file(GLOB plugin_core_net_h *.h)

add_library(plugin_core_net SHARED ${plugin_core_net_cc} ${plugin_core_net_h})

add_definitions(-DSQUICK_NONCLIENT_BUILD)
set_target_properties( plugin_core_net PROPERTIES OUTPUT_NAME "net")
set_target_properties( plugin_core_net PROPERTIES PREFIX "")
set_target_properties( plugin_core_net PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH})
	
target_link_libraries(plugin_core_net libevent.a)
target_link_libraries(plugin_core_net libevent_core.a)
target_link_libraries(plugin_core_net libevent_extra.a)
#target_link_libraries(plugin_core_net libevent_openssl.a)
#target_link_libraries(plugin_core_net libssl.a)
#target_link_libraries(plugin_core_net libcrypto.a)
#target_link_libraries(plugin_core_net squick_struct)
target_link_libraries(plugin_core_net -static-libstdc++)
add_definitions(
	-D_THREAD_SAFE
)
