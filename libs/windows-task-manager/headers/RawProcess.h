#pragma once

#include <Windows.h>
#include <tlhelp32.h>

class RawProcess
{
public:
	struct Statistics
	{
		double CPUUsage;
		double PID;
	};

	RawProcess() = default;
	RawProcess(DWORD Pid);
	virtual ~RawProcess();
	RawProcess(const RawProcess&) = delete;
	RawProcess& operator=(const RawProcess&) = delete;
	RawProcess(RawProcess&&);
	RawProcess& operator=(RawProcess&&);

	bool Open(DWORD PID);
	void Close();
	bool IsOpened() const;
	void Update();
	HANDLE Data();

	Statistics GetStatistics() const;

private:
	void Assign(ULARGE_INTEGER& Left, FILETIME& Right);
	void InitCPUTracker();
	double GetCpuUsage();
	void ClearData();

private:
	HANDLE Handle;
	ULARGE_INTEGER LastCPU;
	ULARGE_INTEGER LastSysCPU;
	ULARGE_INTEGER LastUserCPU;
	Statistics Statistics_;
};