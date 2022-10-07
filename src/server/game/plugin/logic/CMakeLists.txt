set(ProjectName "plugin_extend_game_logic")
file(GLOB plugin_extend_game_logic_cc
	*.cc)

file(GLOB plugin_extend_game_logic_h 
	*.h)	

add_library(plugin_extend_game_logic SHARED
	${plugin_extend_game_logic_cc}
	${plugin_extend_game_logic_h})

set_target_properties( plugin_extend_game_logic PROPERTIES OUTPUT_NAME "logic")
set_target_properties( plugin_extend_game_logic PROPERTIES PREFIX "")
set_target_properties( plugin_extend_game_logic PROPERTIES 
	ARCHIVE_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game
	RUNTIME_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game
	LIBRARY_OUTPUT_DIRECTORY ${SQUICK_BUILD_EXTEND_PLUGIN_PATH}/game )

add_definitions(
-DELPP_NO_DEFAULT_LOG_FILE
)
