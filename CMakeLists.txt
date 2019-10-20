cmake_minimum_required(VERSION 3.10)

project(tanks_shooter CXX)

set(SFML_PREBUILD_PATH ${PROJECT_SOURCE_DIR}/3rdparty/sfml_2.5.1)

add_subdirectory(src)
