cmake_minimum_required(VERSION 3.10)

project(tanks_shooter CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SFML_PREBUILD_PATH ${PROJECT_SOURCE_DIR}/3rdparty/sfml_2.5.1)

add_subdirectory(src)