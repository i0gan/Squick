file(GLOB squick_core_cc
	*.cc)
file(GLOB squick_core_h
	*.h)

add_library(squick_core SHARED ${squick_core_h} ${squick_core_cc})

target_link_libraries(squick_core  squick_struct)
add_dependencies(squick_core  squick_struct)

add_definitions(-DSQUICK_NONCLIENT_BUILD)
set_target_properties( squick_core PROPERTIES OUTPUT_NAME "squick_core")
set_target_properties( squick_core PROPERTIES PREFIX "")
set_target_properties( squick_core PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH} )