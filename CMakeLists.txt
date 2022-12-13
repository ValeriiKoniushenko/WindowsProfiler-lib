cmake_minimum_required(VERSION 3.20.0)

project(WindowsProcessManager)

set (CMAKE_CXX_STANDARD 20)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/Debug/x64)
else()
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/Release/x64)
endif()

add_subdirectory(windows-task-manager)
add_subdirectory(examples)
