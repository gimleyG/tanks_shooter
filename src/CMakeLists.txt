cmake_minimum_required(VERSION 3.10)

set(SHOOTER_LIB ${PROJECT_NAME}-core)
add_subdirectory(shooter)

set(APP_NAME ${PROJECT_NAME}-app)
add_executable(${APP_NAME} main.cpp)
target_link_libraries(${APP_NAME}
    PRIVATE ${SHOOTER_LIB}
)