cmake_minimum_required(VERSION 3.20.0)

project(WindowsProcessManager)

add_subdirectory(libs/windows-task-manager)
add_subdirectory(examples)

add_custom_target(
        doc ALL
        COMMAND doxygen ../Doxyfile
)