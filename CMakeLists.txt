include(${CMAKE_SOURCE_DIR}/cmake/Version.cmake)

cmake_minimum_required(VERSION 3.5)
project(trayicon LANGUAGES CXX)
set_git_tag_as_project_version()
set(PROJECT_VERSION ${PROJECT_VERSION_TAG})

message(STATUS "Project version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build tests: ${BUILD_TESTING}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

configure_file(${CMAKE_SOURCE_DIR}/include/version.h.in
               ${CMAKE_SOURCE_DIR}/include/version.h @ONLY)

add_subdirectory(src)
add_subdirectory(app)
