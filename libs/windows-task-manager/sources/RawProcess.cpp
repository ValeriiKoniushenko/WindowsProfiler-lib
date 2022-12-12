#include "RawProcess.h"

#include <memory>
#include <thread>
#include <cmath>

RawProcess::RawProcess(RawProcess&& Other) :
	CPUTracker_(Handle),
	MemoryTracker_(Handle)
{
	*this = std::move(Other);
}

RawProcess::RawProcess(DWORD Pid) :
	CPUTracker_(Handle),
	MemoryTracker_(Handle)
{
	Open(Pid);
}

RawProcess::RawProcess() :
	CPUTracker_(Handle),
	MemoryTracker_(Handle)
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
		return false;

	CPUTracker_.InitCPUTracker();

	Statistics_.PID = PID;
	Statistics_.Name = ProcessIdToName(PID);

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

std::string RawProcess::ProcessIdToName(DWORD processId)
{
	std::string ret;
	HANDLE handle = OpenProcess(
		PROCESS_QUERY_LIMITED_INFORMATION,
		FALSE,
		processId /* This is the PID, you can find one from windows task manager */
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
			printf("Error GetModuleBaseNameA : %lu", GetLastError());
		}
		CloseHandle(handle);
	}
	else
	{
		printf("Error OpenProcess : %lu", GetLastError());
	}
	return ret;
}
