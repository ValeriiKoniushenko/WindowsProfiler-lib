#include "TaskManager.h"
#include "Utils.h"
#include <iostream>

int main()
{
	TaskManager Manager;
	Manager.Scan();

	for (auto& Process : Manager)
	{
		Process.Update();
		auto RamUsage = Utils::b2Fit(Process.GetStatistics().RAMUsage);
		std::cout << RamUsage.first << " " << Utils::Uits2String(RamUsage.second) << std::endl;
	}

	return 0;
}