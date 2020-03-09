project (doipgen)
set (APP_NAME doipgen)

file(GLOB_RECURSE SOURCES
    ../src/*.cpp
)

add_compile_options (--std=c++1y -g)

include_directories(
    "../src"
    "../src/parser"
    "../src/transport"
)

link_libraries (pthread)
add_executable (${APP_NAME} ${SOURCES})

install(TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/opt/${APP_NAME}/bin)
install(FILES ../etc/config.json PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION ${CMAKE_INSTALL_BINDIR}/opt/${APP_NAME}/etc)
