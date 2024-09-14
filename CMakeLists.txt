cmake_minimum_required(VERSION 3.29)
project(SomeApp)
set(CMAKE_CXX_STANDARD 23)

find_package(Dawn)
find_package(glfw3)

message(STATUS "${PROJECT_NAME} - Using GLFW: Version ${glfw3_VERSION}")

add_library(SomeApp
        SomeApp/App.cpp
        SomeApp/App.h
        SomeApp/callbacks.h
        SomeApp/log.cpp
        SomeApp/log.h
        SomeApp/ColorAttachmentBuilder.h
        SomeApp/ColorAttachmentBuilder.cpp
        SomeApp/BufferBuilder.h
        SomeApp/create.cpp
        SomeApp/create.h
        SomeApp/BindGroup.cpp
        SomeApp/BindGroup.h
)

target_include_directories(SomeApp PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(SomeApp PUBLIC dawn::webgpu_dawn glm glfw)