#include "TaskManager.h"
#include "Utils.h"
#include <iostream>

int main()
{
	TaskManager Manager;
	Manager.Scan();

	for (auto& Stat : Manager.ExtrudeStatisticsFromProcesses())
	{
		std::cout << Stat << std::endl;
	}

	return 0;
}