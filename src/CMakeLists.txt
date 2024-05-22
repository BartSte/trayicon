find_package(Qt6 COMPONENTS Widgets)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*")
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/*")

add_library(trayiconapp ${SOURCES} ${INCLUDES})
target_include_directories(
  trayiconapp
  PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/3rdparty/include
  INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/snapshot_autogen/include)

set(LINK_LIBS spdlog cxxopts Qt6::Widgets)

target_link_libraries(trayiconapp PUBLIC ${LINK_LIBS})
