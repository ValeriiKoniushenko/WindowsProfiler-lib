#pragma once

#include "Object.h"

#include <string>
#include <Windows.h>
#include <tlhelp32.h>

/**
 * @brief Allows to track CPU data
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

	/**
	 * @brief Try to clear data for overloaded operator= and for copy\move constructs
	 * @return void
	 * @param void
	 */
	virtual void ClearData() override;

	/**
	 * @brief Init CPU tracker
	 * @return void
	 * @param void
	 */
	void InitCPUTracker();

	/**
	 * @brief return a current CPU usage in percent
	 * @return void
	 * @param void
	 */
	double GetCpuUsage();

	/**
	 * @brief returns a process priority
	 * @return std::string
	 * @param void
	 */
	std::string GetPriority() const;

private:
	HANDLE* Handle{};
	ULARGE_INTEGER LastCPU{};
	ULARGE_INTEGER LastSysCPU{};
	ULARGE_INTEGER LastUserCPU{};
};