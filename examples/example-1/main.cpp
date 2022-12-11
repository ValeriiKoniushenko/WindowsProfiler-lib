#include "RawProcess.h"
#include <iostream>

int main()
{
	RawProcess Process(8020);

	if (!Process.IsOpened())
	{
		std::cout << "Can't open a process" << std::endl;
		return 1;
	}

	Process.Update();
	std::cout << Process.GetStatistics().CPUUsage << std::endl;
	Sleep(100);

	Process.Update();
	std::cout << Process.GetStatistics().CPUUsage << std::endl;
	Sleep(100);

	Process.Update();
	std::cout << Process.GetStatistics().CPUUsage << std::endl;
	Sleep(100);

	Process.Update();
	std::cout << Process.GetStatistics().CPUUsage << std::endl;


	return 0;
}