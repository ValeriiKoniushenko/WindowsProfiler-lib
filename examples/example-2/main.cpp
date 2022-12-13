#include "RawProcess.h"
#include <iostream>

int main()
{
	RawProcess FurMark(12144);

	FurMark.Update();
	auto Statistics = FurMark.GetStatistics();

	std::cout << Statistics.PID << std::endl;
	std::cout << Statistics.Name << std::endl;
	std::cout << Statistics.CPUUsage << std::endl;
	std::cout << Statistics.RAMUsage << std::endl;
	std::cout << Statistics.VirtualMemoryUsage << std::endl;
	std::cout << Statistics.PathToProcess << std::endl;

	// => 12144
	// => cpuburner
	// => 0
	// => 19222528
	// => 26148864
	// => C:\Program Files (x86)\Geeks3D\Benchmarks\FurMark\cpuburner.exe

	return 0;
}