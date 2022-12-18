#pragma once

#include "CPUTracker.h"
#include "MemoryTracker.h"
#include "Object.h"

#include <ostream>
#include <string>

/**
 * @brief The main class that represent one process.
 */
class RawProcess : public Object
{
public:
	/**
	 * @brief Describes statistics for one process
	 */
	struct Statistics
	{
		std::string Name;
		double CPUUsage{};
		DWORD PID{};
		std::size_t RAMUsage{};
		std::size_t VirtualMemoryUsage{};
		std::string PathToProcess;
		CPUTracker::Priority Priority;
	};

	RawProcess();
	RawProcess(DWORD Pid);
	virtual ~RawProcess();
	RawProcess(const RawProcess&) = delete;
	RawProcess& operator=(const RawProcess&) = delete;
	RawProcess(RawProcess&&);
	RawProcess& operator=(RawProcess&&);

	/**
	 * @brief You can pass PID and monitor only one process
	 * @param DWORD Pid
	 * @return bool - tru if opened, false - in other casese
	 */
	bool Open(DWORD PID);

	/**
	 * @brief Close your handler\your monitoring
	 * @param void
	 * @return void
	 */
	void Close();

	/**
	 * @brief Check if a process was opened successfully
	 * @param void
	 * @return bool - true if successfully, false - in other cases
	 */
	bool IsOpened() const;

	/**
	 * @brief Update process status. Call every time before getting of the statistics
	 * @param void
	 * @return bool - true if successfully, false - in other cases
	 */
	void Update();

	/**
	 * @brief Get raw data
	 * @param void
	 * @return HANDLE
	 */
	HANDLE Data();

	/**
	 * @brief Get statistics for one process
	 * @param void
	 * @return Statistics
	 */
	Statistics GetStatistics() const;

private:
	void ClearData() override;
	std::string ProcessIdToProcessPath(DWORD processId);

private:
	HANDLE Handle{};
	CPUTracker CPUTracker_;
	MemoryTracker MemoryTracker_;
	Statistics Statistics_;
};

std::ostream& operator<<(std::ostream& out, const RawProcess::Statistics& Stat);
