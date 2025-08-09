cmake_minimum_required(VERSION 3.0)

project(clippy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cpp caching.cpp)
add_subdirectory(clip)

target_include_directories(${PROJECT_NAME} PUBLIC clip)
target_link_libraries(${PROJECT_NAME} PUBLIC clip)
