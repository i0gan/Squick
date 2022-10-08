set(ProjectName "squick_exe")

file(GLOB squick_exe_cc *.cc)
file(GLOB squick_exe_h *.h)

add_executable(squick_exe ${squick_exe_cc} ${squick_exe_h})

#add_dependencies(squick_exe  squick_struct)
add_dependencies(squick_exe squick_core squick_struct)
target_link_libraries( squick_exe -pthread libprotobuf.so squick_core squick_struct)

set_target_properties( squick_exe PROPERTIES OUTPUT_NAME "squick")
set_target_properties( squick_exe PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXE_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXE_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXE_PATH} )

add_definitions(-D_X64 -D_CONSOLE)


add_subdirectory(db)
add_subdirectory(login)
add_subdirectory(game)
add_subdirectory(master)
add_subdirectory(proxy)
add_subdirectory(world)

add_subdirectory(misc)

