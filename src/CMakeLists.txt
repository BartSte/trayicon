find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
message(STATUS "Qt6 found at: ${Qt6_DIR}")
get_target_property(QT6_LIB_TYPE Qt6::Widgets TYPE)
set(QT6_LIB_TYPE
  ${QT6_LIB_TYPE}
  CACHE STRING "Type of the Qt6 library (STATIC_LIBRARY or SHARED_LIBRARY)")
message(STATUS "Qt6 library type: ${QT6_LIB_TYPE}")

set(_3rdparty "${CMAKE_SOURCE_DIR}/3rdparty/include")
file(GLOB_RECURSE SPDLOG_HEADERS "${_3rdparty}/spdlog/*")
add_library(spdlog ${SPDLOG_HEADERS})
add_library(cxxopts "${_3rdparty}/cxxopts.hpp")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*")
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/*")
add_library(trayiconapp ${SOURCES} ${INCLUDES})
target_include_directories(
  trayiconapp
  PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/3rdparty/include)

if(WIN32)
  message(STATUS "Linking trayiconapp for Windows")
  target_link_libraries(trayiconapp PUBLIC spdlog cxxopts Qt6::Widgets)

elseif(UNIX AND NOT APPLE)
  message(STATUS "Linking trayiconapp for Linux")
  target_link_libraries(trayiconapp PUBLIC spdlog cxxopts Qt6::Widgets Qt6::QWaylandIntegrationPlugin Qt6::QXcbIntegrationPlugin)

else()
  message(FATAL_ERROR "Unsupported platform for linking trayiconapp")
endif()
