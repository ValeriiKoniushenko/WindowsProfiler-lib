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


#include "CPUTracker.h"

#include <cmath>
#include <thread>

namespace
{
void Assign(ULARGE_INTEGER& Left, FILETIME& Right)
{
	memcpy(&Left, &Right, sizeof(FILETIME));
}
}	 // namespace

CPUTracker::CPUTracker(HANDLE& Handle) : Handle(&Handle)
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
	double percent = (Sys.QuadPart - LastSysCPU.QuadPart) + (User.QuadPart - LastUserCPU.QuadPart);
	percent /= (Now.QuadPart - LastCPU.QuadPart);
	percent /= std::thread::hardware_concurrency();
	LastCPU = Now;
	LastUserCPU = User;
	LastSysCPU = Sys;

	if (std::isnan(percent) || std::isinf(percent))
	{
		percent = 0.;
	}

	return percent * 100.;
}

CPUTracker::~CPUTracker()
{
	ClearData();
}

CPUTracker::Priority CPUTracker::GetPriority() const
{
	return static_cast<Priority>(GetPriorityClass(*Handle));
}
