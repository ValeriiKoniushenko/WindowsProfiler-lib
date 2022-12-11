add_library(
	WindowsTaskManager
	sources/RawProcess.cpp
)

target_include_directories(
	WindowsTaskManager PUBLIC
	headers/
)