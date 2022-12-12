#include "CPUTracker.h"

#include <thread>
#include <cmath>

namespace
{
	void Assign(ULARGE_INTEGER& Left, FILETIME& Right)
	{
		memcpy(&Left, &Right, sizeof(FILETIME));
	}
} // namespace

CPUTracker::CPUTracker(HANDLE& Handle) :
	Handle(&Handle)
{
}

void CPUTracker::ClearData()
{
	Handle = {};
	LastCPU = {};
	LastSysCPU = {};
	LastUserCPU = {};
}

void CPUTracker::InitCPUTracker()
{
	FILETIME FTime, FSys, FUser;

	GetSystemTimeAsFileTime(&FTime);
	Assign(LastCPU, FTime);

	GetProcessTimes(*Handle, &FTime, &FTime, &FSys, &FUser);
	Assign(LastSysCPU, FSys);
	Assign(LastUserCPU, FUser);
}

double CPUTracker::GetCpuUsage()
{
	FILETIME FTime, FSys, FUser;
	ULARGE_INTEGER Now, Sys, User;

	GetSystemTimeAsFileTime(&FTime);
	Assign(Now, FTime);

	GetProcessTimes(*Handle, &FTime, &FTime, &FSys, &FUser);
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

CPUTracker::~CPUTracker()
{
	ClearData();
}
