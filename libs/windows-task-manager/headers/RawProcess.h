#pragma once

#include "CPUTracker.h"
#include "MemoryTracker.h"
#include "Object.h"

class RawProcess : public Object
{
public:
	struct Statistics
	{
		double CPUUsage{};
		DWORD PID{};
		std::size_t RAMUsage;
		std::size_t VirtualMemoryUsage;
	};

	RawProcess();
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
	void ClearData() override;

private:
	HANDLE Handle{};
	CPUTracker CPUTracker_;
	MemoryTracker MemoryTracker_;
	Statistics Statistics_;
};