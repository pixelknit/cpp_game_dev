cmake_minimum_required(VERSION 3.11)
project(ui_module)
set(CMAKE_CXX_STANDARD 20)
set(glfw3_DIR "C:/Program Files (x86)/GLFW/lib/cmake/glfw3")

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(third_party/imgui)

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui
    imgui_stdlib
    imgui_glfw
    imgui_opengl3
    glfw
    OpenGL::GL
)