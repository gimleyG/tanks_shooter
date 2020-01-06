cmake_minimum_required(VERSION 3.10)

set(SOURCES
    game.h
    game.cpp

    menu/splash_screen.h
    menu/splash_screen.cpp
    menu/main.h
    menu/main.cpp
)

find_library(SFML_WINDOW NAMES sfml-window-d PATHS ${SFML_PREBUILD_PATH}/lib)
find_library(SFML_SYSTEM NAMES sfml-system-d PATHS ${SFML_PREBUILD_PATH}/lib)
find_library(SFML_GRAPHICS NAMES sfml-graphics-d PATHS ${SFML_PREBUILD_PATH}/lib)
find_library(SFML_FREETYPE NAMES freetype PATHS ${SFML_PREBUILD_PATH}/lib)

add_library(${SHOOTER_LIB} STATIC ${SOURCES})
target_include_directories(${SHOOTER_LIB}
    PUBLIC ${SFML_PREBUILD_PATH}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${SHOOTER_LIB}
    PRIVATE ${SFML_SYSTEM}
    PRIVATE ${SFML_WINDOW}
    PRIVATE ${SFML_GRAPHICS}
    PRIVATE ${SFML_FREETYPE}
)

file(COPY ${SFML_PREBUILD_PATH}/bin/sfml-window-d-2.dll
         DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(COPY ${SFML_PREBUILD_PATH}/bin/sfml-system-d-2.dll
         DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(COPY ${SFML_PREBUILD_PATH}/bin/sfml-graphics-d-2.dll
         DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
