cmake_minimum_required(VERSION 3.11)                      
                                                          
# Core ImGui library                                      
add_library(imgui STATIC                                  
    imgui.cpp                                             
    imgui_demo.cpp                                        
    imgui_draw.cpp                                        
    imgui_widgets.cpp                                     
    imgui_tables.cpp                                      
)                                                         
                                                          
target_include_directories(imgui PUBLIC                   
    ${CMAKE_CURRENT_SOURCE_DIR}                           
)                                                         
                                                          
add_library(imgui_stdlib STATIC                           
    misc/cpp/imgui_stdlib.cpp                             
)                                                         
target_link_libraries(imgui_stdlib PUBLIC imgui)          
                                                          
# Example for GLFW + OpenGL3:                             
add_library(imgui_glfw STATIC                             
    backends/imgui_impl_glfw.cpp                          
)                                                         
target_link_libraries(imgui_glfw PUBLIC imgui glfw)       
                                                          
add_library(imgui_opengl3 STATIC                          
    backends/imgui_impl_opengl3.cpp                       
)                                                         
target_link_libraries(imgui_opengl3 PUBLIC imgui) 