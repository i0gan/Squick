set(ProjectName "core_plugin_no_sql")

set(ProjectName "core_plugin_no_sql")
file(GLOB core_plugin_no_sql_cc
		*.cc)
file(GLOB core_plugin_no_sql_h
		*.h)

add_library(core_plugin_no_sql SHARED
		${core_plugin_no_sql_cc}
		${core_plugin_no_sql_h})

set_target_properties( core_plugin_no_sql PROPERTIES OUTPUT_NAME "nosql")
set_target_properties( core_plugin_no_sql PROPERTIES PREFIX "")
set_target_properties( core_plugin_no_sql PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
		RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH}
		LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_CORE_PLUGIN_PATH} )
target_link_libraries(core_plugin_no_sql hiredis.a)
target_link_libraries(core_plugin_no_sql -static-libstdc++)
add_definitions(
		-DELPP_NO_DEFAULT_LOG_FILE
)


