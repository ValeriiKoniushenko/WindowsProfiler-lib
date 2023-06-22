// MIT License
//
// Copyright (c) 2023 Valerii Koniushenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// 														 copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
