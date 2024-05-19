cmake_minimum_required(VERSION 3.5)
project(kmonadtray LANGUAGES CXX)
set(PROJECT_VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(src)
add_subdirectory(app)
