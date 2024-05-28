find_package(Qt6 REQUIRED COMPONENTS Widgets)
message(STATUS "Qt6 found at: ${Qt6_DIR}")

qt_standard_project_setup()

set(_3rdparty "${CMAKE_SOURCE_DIR}/3rdparty/include")
file(GLOB_RECURSE SPDLOG_HEADERS "${_3rdparty}/spdlog/*")
add_library(spdlog ${SPDLOG_HEADERS})
add_library(cxxopts "${_3rdparty}/cxxopts.hpp")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*")
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/*")
add_library(trayiconapp ${SOURCES} ${INCLUDES})
target_include_directories(
  trayiconapp
  PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/3rdparty/include
  INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/snapshot_autogen/include)

if(WIN32)
  set(LINK_LIBS spdlog cxxopts Qt6::Widgets)
else()
  set(LINK_LIBS spdlog cxxopts Qt6::Widgets Qt6::QWaylandIntegrationPlugin
                Qt6::QXcbIntegrationPlugin)
endif()

target_link_libraries(trayiconapp PUBLIC ${LINK_LIBS})
