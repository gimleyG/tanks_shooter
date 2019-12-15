cmake_minimum_required(VERSION 3.10)

set(SOURCES
    game.h
    game.cpp
)

find_library(SFML_WINDOW NAMES sfml-window-d PATHS ${SFML_PREBUILD_PATH}/lib)
find_library(SFML_SYSTEM NAMES sfml-system-d PATHS ${SFML_PREBUILD_PATH}/lib)
find_library(SFML_FREETYPE NAMES freetype PATHS ${SFML_PREBUILD_PATH}/lib)

add_library(${SHOOTER_LIB} STATIC ${SOURCES})
target_include_directories(${SHOOTER_LIB}
    PRIVATE ${SFML_PREBUILD_PATH}/include
)
target_link_libraries(${SHOOTER_LIB}
    PRIVATE ${SFML_SYSTEM}
    PRIVATE ${SFML_WINDOW}
    PRIVATE ${SFML_FREETYPE}
)

file(COPY ${SFML_PREBUILD_PATH}/bin/sfml-window-d-2.dll
         DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(COPY ${SFML_PREBUILD_PATH}/bin/sfml-system-d-2.dll
         DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})