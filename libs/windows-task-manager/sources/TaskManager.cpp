#include "TaskManager.h"

#include <Windows.h>
#include <tlhelp32.h>

bool TaskManager::Scan()
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessSnap, &pe32))
	{
		while (Process32Next(hProcessSnap, &pe32))
		{
			RawProcess Process(pe32.th32ProcessID);
			if (!Process.IsOpened())
			{
				continue;
			}

			auto El = Processes.find(pe32.th32ProcessID);
			if (El == Processes.end())
			{
				Processes.emplace(pe32.th32ProcessID, std::move(Process));
			}
			else
			{
				El->second.Update();
			}
		}
	}

	CloseHandle(hProcessSnap);

	return true;
}

TaskManager::ContainerT::iterator TaskManager::begin()
{
	return Processes.begin();
}

TaskManager::ContainerT::const_iterator TaskManager::begin() const
{
	return Processes.cbegin();
}

TaskManager::ContainerT::iterator TaskManager::end()
{
	return Processes.end();
}

TaskManager::ContainerT::const_iterator TaskManager::end() const
{
	return Processes.cend();
}

TaskManager::ContainerT& TaskManager::GetProcesses()
{
	return Processes;
}

const TaskManager::ContainerT& TaskManager::GetProcesses() const
{
	return Processes;
}

std::vector<RawProcess::Statistics> TaskManager::ExtrudeStatisticsFromProcesses() const
{
	std::vector<RawProcess::Statistics> Data;

	for (auto& Process : Processes)
	{
		Data.emplace_back(Process.second.GetStatistics());
	}

	return Data;
}
