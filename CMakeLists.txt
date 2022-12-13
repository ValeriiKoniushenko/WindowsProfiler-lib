cmake_minimum_required(VERSION 3.20.0)

project(WindowsProcessManager)

set (CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/windows-task-manager)
add_subdirectory(examples)
