#include "RawProcess.h"

#include <memory>
#include <thread>
#include <cmath>

void RawProcess::Close()
{
	CloseHandle(Handle);

	ClearData();
}

bool RawProcess::IsOpened() const
{
	return Handle != NULL;
}

RawProcess::RawProcess(RawProcess&& Other)
{
	*this = std::move(Other);
}

RawProcess& RawProcess::operator=(RawProcess&& Other)
{
	Handle = Other.Handle;
	LastCPU = Other.LastCPU;
	LastSysCPU = Other.LastSysCPU;
	LastUserCPU = Other.LastUserCPU;
	Statistics_ = Other.Statistics_;

	Other.ClearData();

	return *this;
}

void RawProcess::Update()
{
	Statistics_.CPUUsage = GetCpuUsage();
}

RawProcess::RawProcess(DWORD Pid)
{
	Open(Pid);
}

bool RawProcess::Open(DWORD PID)
{
	if (IsOpened())
	{
		Close();
	}

	Handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);

	Statistics_.PID = PID;

	InitCPUTracker();

	return IsOpened();
}

HANDLE RawProcess::Data()
{
	return Handle;
}

void RawProcess::Assign(ULARGE_INTEGER& Left, FILETIME& Right)
{
	memcpy(&Left, &Right, sizeof(FILETIME));
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

void RawProcess::InitCPUTracker()
{
	FILETIME FTime, FSys, FUser;

	GetSystemTimeAsFileTime(&FTime);
	Assign(LastCPU, FTime);

	GetProcessTimes(Handle, &FTime, &FTime, &FSys, &FUser);
	Assign(LastSysCPU, FSys);
	Assign(LastUserCPU, FUser);
}

double RawProcess::GetCpuUsage()
{
	FILETIME FTime, FSys, FUser;
	ULARGE_INTEGER Now, Sys, User;

	GetSystemTimeAsFileTime(&FTime);
	Assign(Now, FTime);

	GetProcessTimes(Handle, &FTime, &FTime, &FSys, &FUser);
	Assign(Sys, FSys);
	Assign(User, FUser);
	double percent = (Sys.QuadPart - LastSysCPU.QuadPart) +
					 (User.QuadPart - LastUserCPU.QuadPart);
	percent /= (Now.QuadPart - LastCPU.QuadPart);
	percent /= std::thread::hardware_concurrency();
	LastCPU = Now;
	LastUserCPU = User;
	LastSysCPU = Sys;

	if (std::isnan(percent) || std::isinf(percent))
		percent = 0.;

	return percent * 100.;
}

void RawProcess::ClearData()
{
	Handle = {};
	LastCPU = {};
	LastSysCPU = {};
	LastUserCPU = {};
	Statistics_ = {};
}
