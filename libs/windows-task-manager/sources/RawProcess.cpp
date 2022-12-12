#include "RawProcess.h"

#include <memory>
#include <thread>
#include <cmath>

RawProcess::RawProcess(RawProcess&& Other) :
	CPUTracker_(Handle)
{
	*this = std::move(Other);
}

RawProcess::RawProcess(DWORD Pid) :
	CPUTracker_(Handle)
{
	Open(Pid);
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
}

bool RawProcess::Open(DWORD PID)
{
	if (IsOpened())
	{
		Close();
	}

	Handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);

	Statistics_.PID = PID;

	CPUTracker_.InitCPUTracker();

	return IsOpened();
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
