find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

include(${CMAKE_SOURCE_DIR}/cmake/Install.cmake)

# TODO: I have the issue that the default icon can not be found...
add_executable(trayicon main.cpp ${CMAKE_SOURCE_DIR}/resources/resources.qrc)
target_link_libraries(trayicon PRIVATE trayiconapp)

if(UNIX AND NOT APPLE)
  install(PROGRAMS ${INSTALL_SCRIPTS}/${PROJECT_NAME} DESTINATION .)
  install_with_runtime_dependencies(trayicon)
elseif(WIN32)
  install(PROGRAMS ${CMAKE_BINARY_DIR}/app/Release/trayicon.exe DESTINATION .)
endif()
