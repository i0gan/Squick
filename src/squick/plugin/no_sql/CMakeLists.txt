set(ProjectName "plugin_core_no_sql")

set(ProjectName "plugin_core_no_sql")
file(GLOB plugin_core_no_sql_cc
		*.cc)
file(GLOB plugin_core_no_sql_h
		*.h)

add_library(plugin_core_no_sql SHARED
		${plugin_core_no_sql_cc}
		${plugin_core_no_sql_h})

set_target_properties( plugin_core_no_sql PROPERTIES OUTPUT_NAME "nosql")
set_target_properties( plugin_core_no_sql PROPERTIES PREFIX "")
set_target_properties( plugin_core_no_sql PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
		RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH}
		LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_PLUGIN_CORE_PATH} )
target_link_libraries(plugin_core_no_sql hiredis.a)
target_link_libraries(plugin_core_no_sql -static-libstdc++)
add_definitions(
		-DELPP_NO_DEFAULT_LOG_FILE
)


