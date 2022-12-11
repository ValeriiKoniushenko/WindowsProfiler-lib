
add_executable(Example1 main.cpp)

target_link_libraries(
	Example1 PUBLIC 
	WindowsTaskManager
)

target_compile_features(Example1 PRIVATE cxx_std_17)

