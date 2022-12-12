add_library(
	WindowsTaskManager
		sources/CPUTracker.cpp
		sources/MemoryTracker.cpp
		sources/Object.cpp
		sources/RawProcess.cpp
		sources/Utils.cpp

		headers/CPUTracker.h
		headers/MemoryTracker.h
		headers/Object.h
		headers/RawProcess.h
		headers/Utils.h
)

target_include_directories(
	WindowsTaskManager PUBLIC
	headers/
)