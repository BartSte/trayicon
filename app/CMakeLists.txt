find_package(Qt6 REQUIRED COMPONENTS Core)
add_executable(${PROJECT_NAME} main.cpp
                               ${CMAKE_SOURCE_DIR}/resources/resources.qrc)
target_link_libraries(${PROJECT_NAME} PRIVATE trayiconapp)
