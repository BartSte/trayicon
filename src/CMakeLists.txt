find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(Qt6 COMPONENTS Widgets)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*")
file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/*")

add_library(kmonadtray ${SOURCES} ${INCLUDES})
target_include_directories(
  kmonadtray
  PUBLIC ${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS}
  INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/snapshot_autogen/include)

set(LINK_LIBS spdlog::spdlog_header_only Boost::boost Boost::filesystem
              Qt6::Widgets)

target_link_libraries(kmonadtray PUBLIC ${LINK_LIBS})
