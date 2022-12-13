add_library(
	WindowsTaskManager STATIC
		sources/CPUTracker.cpp
		sources/MemoryTracker.cpp
		sources/Object.cpp
		sources/RawProcess.cpp
		sources/TaskManager.cpp
		sources/Utils.cpp

		headers/CPUTracker.h
		headers/MemoryTracker.h
		headers/Object.h
		headers/RawProcess.h
		headers/TaskManager.h
		headers/Utils.h
)

target_include_directories(
	WindowsTaskManager PUBLIC
	headers/
	D:/LibsUtils/boost_1_80_0
)