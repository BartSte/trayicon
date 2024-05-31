include(${CMAKE_SOURCE_DIR}/cmake/Install.cmake)

add_executable(${PROJECT_NAME}_bin main.cpp
                            ${CMAKE_SOURCE_DIR}/resources/resources.qrc)

target_link_libraries(${PROJECT_NAME}_bin PRIVATE trayiconapp)

install(PROGRAMS ${INSTALL_SCRIPTS}/${PROJECT_NAME} DESTINATION .)
install_with_runtime_dependencies(${PROJECT_NAME}_bin)
