#include "RawProcess.h"
#include "Utils.h"
#include <iostream>

int main()
{
	RawProcess Process(7204);

	if (!Process.IsOpened())
	{
		std::cout << "Can't open a process" << std::endl;
		return 1;
	}

	Process.Update();
	Sleep(100);

	Process.Update();
	auto Statistics = Process.GetStatistics();
	std::cout << Statistics.CPUUsage << std::endl;
	std::cout << Utils::b2Mb(Statistics.RAMUsage) << std::endl;
	std::cout << Utils::b2Mb(Statistics.VirtualMemoryUsage) << std::endl;
	return 0;
}