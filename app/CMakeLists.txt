add_executable(kmonad-tray main.cpp ${CMAKE_SOURCE_DIR}/resources/resources.qrc)

target_link_libraries(kmonad-tray PRIVATE kmonadtray)
