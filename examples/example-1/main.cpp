#include "RawProcess.h"
#include "windows.h"
#include <iostream>
#include <cmath>
#include <thread>

int main()
{
	RawProcess Process(8020);

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