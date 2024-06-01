if(WIN32)
  # For the binary is called directly hence we call it trayicon.
  set(bin "trayicon")
else()
  # For the binary is called through a script called trayicon.
  set(bin "trayicon_bin")
endif()

include(${CMAKE_SOURCE_DIR}/cmake/Install.cmake)

add_executable(${bin} main.cpp ${CMAKE_SOURCE_DIR}/resources/resources.qrc)
target_link_libraries(${bin} PRIVATE trayiconapp)

if(WIN32)
  message(STATUS "No windows specific install steps")
else()
  install(PROGRAMS ${INSTALL_SCRIPTS}/${PROJECT_NAME} DESTINATION .)
  install_with_runtime_dependencies(${bin})
endif()
