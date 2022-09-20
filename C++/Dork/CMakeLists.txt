cmake_minimum_required(VERSION 3.20)
project(Dork)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(Dork
        Source/main.cpp
        Source/UI/UI.cpp
        Source/World/World.cpp Source/World/Physics.cpp Source/World/Entity.cpp Source/World/Shape.cpp
        Source/World/Shapes/
        ImGuiBindings/imgui_impl_opengl3.cpp ImGuiBindings/imgui_impl_sdl.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach (dir ${dirs})
    message(STATUS "dir='${dir}'")
endforeach ()