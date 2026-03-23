cmake_minimum_required(VERSION 3.28)
project(myproject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
  PUBLIC
    main.cpp
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
      helloworld.cpp
)
