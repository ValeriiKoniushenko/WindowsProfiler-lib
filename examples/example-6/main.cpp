#include "TaskManager.h"
#include "Utils.h"

#include <algorithm>
#include <iostream>

int main()
{
	TaskManager Tasker;

	Tasker.Scan();
	Sleep(100);

	Tasker.Scan();
	auto Data = Tasker.ExtrudeStatisticsFromProcesses();
	std::sort(Data.begin(), Data.end(), [](auto& a, auto& b) { return a.PID < b.PID; });
	for (auto& Stat : Data)
	{
		std::cout << "(" << Stat.PID << ") ";
		std::cout << Stat.Name << std::endl;
	}

	// => (960) fsnotifier
	// => (1056) nvcontainer
	// => (1088) StartMenuExperienceHost
	// => (1952) chrome
	// => (2092) RuntimeBroker
	// => (2328) TextInputHost
	// ......

	return 0;
}