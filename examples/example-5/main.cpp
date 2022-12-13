#include "TaskManager.h"
#include <iostream>

int main()
{
	TaskManager Tasker;

	Tasker.Scan();
	Sleep(100);

	Tasker.Scan();
	for (auto& Stat : Tasker.ExtrudeStatisticsFromProcesses())
	{
		std::cout << "(" << Stat.PID << ") " ;
		std::cout << Stat.Name << std::endl;
	}

	// => (18616) Example4
	// => (14448) winpty-agent
	// => (7704)  svchost
	// => (14628) conhost
	// => (16892) powershell
	// ......

	return 0;
}