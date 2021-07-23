project (doipgen)
set (APP_NAME doipgen)

file(GLOB_RECURSE SOURCES
    ${WORKING_DIR}/src/*.cc
)

message("${WORKING_DIR}")

add_compile_options (--std=c++1y -g)

include_directories(
    "${WORKING_DIR}/src"
    "${WORKING_DIR}/src/parser"
    "${WORKING_DIR}/src/transport"
    "${WORKING_DIR}/src/report"
)

link_libraries (pthread)
add_executable (${APP_NAME} ${SOURCES})

install(TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/opt/${APP_NAME}/bin)
install(FILES etc/config.json PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION ${CMAKE_INSTALL_BINDIR}/opt/${APP_NAME}/etc)
install(FILES etc/preset.json PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION ${CMAKE_INSTALL_BINDIR}/opt/${APP_NAME}/etc)
install(DIRECTORY var DESTINATION ${CMAKE_INSTALL_BINDIR}/opt/${APP_NAME})

if(ENABLE_TEST)
    add_subdirectory(test)
endif()
