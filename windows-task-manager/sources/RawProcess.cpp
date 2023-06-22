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


#include "RawProcess.h"

#include "boost/format.hpp"

#include <cmath>
#include <filesystem>
#include <memory>
#include <thread>

RawProcess::RawProcess(RawProcess&& Other) : CPUTracker_(Handle), MemoryTracker_(Handle)
{
	*this = std::move(Other);
}

RawProcess::RawProcess(DWORD Pid) : CPUTracker_(Handle), MemoryTracker_(Handle)
{
	Open(Pid);
}

RawProcess::RawProcess() : CPUTracker_(Handle), MemoryTracker_(Handle)
{
}

void RawProcess::Close()
{
	CloseHandle(Handle);
	ClearData();
}

bool RawProcess::IsOpened() const
{
	return Handle != NULL;
}

RawProcess& RawProcess::operator=(RawProcess&& Other)
{
	Handle = Other.Handle;
	Statistics_ = Other.Statistics_;
	CPUTracker_ = Other.CPUTracker_;

	Other.ClearData();

	return *this;
}

void RawProcess::Update()
{
	Statistics_.CPUUsage = CPUTracker_.GetCpuUsage();
	Statistics_.RAMUsage = MemoryTracker_.RAMUsage();
	Statistics_.VirtualMemoryUsage = MemoryTracker_.VirtualMemoryUsage();
	Statistics_.Priority = CPUTracker_.GetPriority();
}

bool RawProcess::Open(DWORD PID)
{
	if (IsOpened())
	{
		Close();
	}

	Handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);
	if (!IsOpened())
	{
		return false;
	}

	CPUTracker_.InitCPUTracker();

	Statistics_.PID = PID;
	Statistics_.PathToProcess = ProcessIdToProcessPath(PID);
	Statistics_.Name = std::filesystem::path(ProcessIdToProcessPath(PID)).stem().string();

	return true;
}

HANDLE RawProcess::Data()
{
	return Handle;
}

RawProcess::~RawProcess()
{
	if (IsOpened())
	{
		Close();
	}
}

RawProcess::Statistics RawProcess::GetStatistics() const
{
	return Statistics_;
}

void RawProcess::ClearData()
{
	Handle = {};
	Statistics_ = {};
	CPUTracker_.ClearData();
}

std::string RawProcess::ProcessIdToProcessPath(DWORD processId)
{
	std::string ret;
	HANDLE handle = OpenProcess(
		PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId /* This is the PID, you can find one from windows task manager */
	);
	if (handle)
	{
		DWORD buffSize = 1024;
		CHAR buffer[1024];
		if (QueryFullProcessImageNameA(handle, 0, buffer, &buffSize))
		{
			ret = buffer;
		}
		else
		{
			return "None";
		}
		CloseHandle(handle);
	}
	else
	{
		return "None";
	}
	return ret;
}

std::ostream& operator<<(std::ostream& out, const RawProcess::Statistics& Stat)
{
	out << boost::format("{ PID: %1%, Name: %2%, CPU Usage: %3%, RAM Usage: %4%, Virtual Memory Usage: %5%, Path: %6% }") %
			   Stat.PID % Stat.Name % Stat.CPUUsage % Stat.RAMUsage % Stat.VirtualMemoryUsage % Stat.PathToProcess;
	return out;
}
