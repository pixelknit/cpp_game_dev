cmake_minimum_required(VERSION 3.11)
project(store_app)
set(CMAKE_CXX_STANDARD 20)

file (GLOB SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include)