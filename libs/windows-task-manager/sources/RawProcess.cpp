#include "RawProcess.h"

#include "boost/format.hpp"

#include <cmath>
#include <memory>
#include <thread>
#include <filesystem>

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
