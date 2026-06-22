cmake_minimum_required(VERSION 3.31)
project(algo VERSION 1.0 LANGUAGES CXX)

add_library(algo INTERFACE)
add_library(algo::algo ALIAS algo)

target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if (PROJECT_IS_TOP_LEVEL)
    add_executable(${PROJECT_NAME}-example examples/main.cpp)
    target_link_libraries(${PROJECT_NAME}-example PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})
endif ()