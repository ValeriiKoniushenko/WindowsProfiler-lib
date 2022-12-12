#pragma once

#include "CPUTracker.h"
#include "MemoryTracker.h"
#include "Object.h"

#include <string>

class RawProcess : public Object
{
public:
	struct Statistics
	{
		std::string Name;
		double CPUUsage{};
		DWORD PID{};
		std::size_t RAMUsage{};
		std::size_t VirtualMemoryUsage{};
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
	std::string ProcessIdToName(DWORD processId);
private:
	HANDLE Handle{};
	CPUTracker CPUTracker_;
	MemoryTracker MemoryTracker_;
	Statistics Statistics_;
};