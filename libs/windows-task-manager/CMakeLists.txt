add_library(
	WindowsTaskManager
		sources/CPUTracker.cpp
		sources/RawProcess.cpp
		sources/Object.cpp

		headers/CPUTracker.h
		headers/RawProcess.h
		headers/Object.h
)

target_include_directories(
	WindowsTaskManager PUBLIC
	headers/
)