set(ProjectName "proxy_server")
file(GLOB soruces *.cc)
file(GLOB headers *.h)
add_library(${ProjectName} SHARED ${soruces} ${headers})
LinkSquick(${ProjectName})
SquickOut(${ProjectName} "server/proxy" ${SQUICK_BUILD_PLUGIN_SERVER_PATH}/proxy "server")