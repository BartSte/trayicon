include(${CMAKE_SOURCE_DIR}/cmake/Version.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Install.cmake)

cmake_minimum_required(VERSION 3.5)
project(trayicon LANGUAGES CXX)
set_git_tag_as_project_version()
set(PROJECT_VERSION ${PROJECT_VERSION_TAG})

message(STATUS "Project version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(INSTALL_SCRIPTS
    ${CMAKE_SOURCE_DIR}/scripts
    CACHE PATH "Install scripts")
set(CMAKE_INSTALL_PREFIX /opt/${PROJECT_NAME})
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

configure_file(${CMAKE_SOURCE_DIR}/include/version.h.in
               ${CMAKE_SOURCE_DIR}/include/version.h @ONLY)

add_subdirectory(src)
add_subdirectory(app)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION_FULL})
set(CPACK_GENERATOR "TGZ")
include(CPack)
