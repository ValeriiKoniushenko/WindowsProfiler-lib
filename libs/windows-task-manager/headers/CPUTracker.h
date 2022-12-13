#pragma once

#include "Object.h"

#include <string>
#include <Windows.h>
#include <tlhelp32.h>

/**
 * @class CPUTracker
 * Hello world
 * @brief about a class
 */
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
	std::string GetPriority() const;

private:
	HANDLE* Handle{};
	ULARGE_INTEGER LastCPU{};
	ULARGE_INTEGER LastSysCPU{};
	ULARGE_INTEGER LastUserCPU{};
};