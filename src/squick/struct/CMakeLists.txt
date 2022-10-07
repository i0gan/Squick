set(ProjectName "squick_struct")


file(GLOB squick_struct_cc *.cc)
file(GLOB squick_struct_h *.h)
# 采用静态编译塞入可执行文件里，由于可执行程序内没有直接调用里面的函数，不存在关系，所以就不能链接关系。

add_library(squick_struct SHARED 
	${squick_struct_cc}
	${squick_struct_h})

add_definitions(
	-D_THREAD_SAFE
)
target_link_libraries(squick_struct libprotobuf.so)

set_target_properties( squick_struct PROPERTIES OUTPUT_NAME "squick_struct")
set_target_properties( squick_struct PROPERTIES PREFIX "")
set_target_properties( squick_struct PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_RUNTIME_LIB_PATH} )