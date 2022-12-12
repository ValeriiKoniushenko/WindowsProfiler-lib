#pragma once

#include "CPUTracker.h"

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

	double GetCpuUsage();

private:
	void ClearData();

private:
	HANDLE Handle{};
	CPUTracker CPUTracker_;
	Statistics Statistics_;
	ULARGE_INTEGER LastCPU{};
	ULARGE_INTEGER LastSysCPU{};
	ULARGE_INTEGER LastUserCPU{};
};