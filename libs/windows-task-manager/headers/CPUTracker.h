#pragma once

#include "Object.h"

#include <Windows.h>
#include <tlhelp32.h>

class CPUTracker : public Object
{
public:
	CPUTracker(HANDLE& Handle);
	~CPUTracker();
	CPUTracker(const CPUTracker&) = default;
	CPUTracker& operator=(const CPUTracker&) = default;
	CPUTracker(CPUTracker&&) = default;
	CPUTracker& operator=(CPUTracker&&) = default;

	virtual void ClearData() override;

	void InitCPUTracker();
	double GetCpuUsage();

private:
	HANDLE* Handle{};
	ULARGE_INTEGER LastCPU{};
	ULARGE_INTEGER LastSysCPU{};
	ULARGE_INTEGER LastUserCPU{};
};