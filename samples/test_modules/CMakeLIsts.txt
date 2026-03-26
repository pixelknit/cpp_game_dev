cmake_minimum_required(VERSION 3.11)
project(ecs_app)
set(CXX_STANDARD_REQUIRED 20)

file (GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
