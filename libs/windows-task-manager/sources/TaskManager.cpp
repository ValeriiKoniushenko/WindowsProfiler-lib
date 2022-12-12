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
	{	 // Gets first running process
		while (Process32Next(hProcessSnap, &pe32))
		{
			RawProcess Process(pe32.th32ProcessID);
			if (!Process.IsOpened())
			{
				continue;
			}

			Processes.emplace_back(std::move(Process));
		}
	}

	CloseHandle(hProcessSnap);

	return true;
}

std::vector<RawProcess>::iterator TaskManager::begin()
{
	return Processes.begin();
}

std::vector<RawProcess>::const_iterator TaskManager::begin() const
{
	return Processes.cbegin();
}

std::vector<RawProcess>::iterator TaskManager::end()
{
	return Processes.end();
}

std::vector<RawProcess>::const_iterator TaskManager::end() const
{
	return Processes.cend();
}
