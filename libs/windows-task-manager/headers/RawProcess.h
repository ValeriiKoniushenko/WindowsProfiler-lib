#pragma once

#include <Windows.h>
#include <tlhelp32.h>

class RawProcess
{
public:
	struct Statistics
	{
		double CPUUsage;
	};

	RawProcess() = default;
	RawProcess(DWORD Pid);
	virtual ~RawProcess();
	RawProcess(const RawProcess&) = default;
	RawProcess& operator=(const RawProcess&) = default;
	RawProcess(RawProcess&&);
	RawProcess& operator=(RawProcess&&);

	bool Open(DWORD Pid);
	void Close();
	bool IsOpened() const;
	void Update();
	HANDLE Data();

	Statistics GetStatistics() const;

private:
	void Assign(ULARGE_INTEGER& Left, FILETIME& Right);
	void InitCPUTracker();
	double GetCpuUsage();

private:
	HANDLE Handle;
	ULARGE_INTEGER LastCPU, LastSysCPU, LastUserCPU;
	Statistics Statistics_;
};