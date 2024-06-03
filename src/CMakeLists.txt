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
  PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/3rdparty/include
  INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/trayiconapp_autogen/include)

if(WIN32)
  message(STATUS "Building for Windows")
  set(LINK_LIBS spdlog cxxopts Qt6::Widgets)

elseif(Unix AND NOT APPLE)
  message(STATUS "Building for Linux")
  if (QT6_LIB_TYPE STREQUAL "STATIC_LIBRARY")
    set(LINK_LIBS spdlog cxxopts Qt6::Widgets Qt6::QWaylandIntegrationPlugin
                  Qt6::QXcbIntegrationPlugin)
  elseif(QT6_LIB_TYPE STREQUAL "SHARED_LIBRARY")
    set(LINK_LIBS spdlog cxxopts Qt6::Widgets)
  else()
    message(FATAL_ERROR "Unknown Qt6 library type: ${QT6_LIB_TYPE}")
  endif()
endif()

target_link_libraries(trayiconapp PUBLIC ${LINK_LIBS})
