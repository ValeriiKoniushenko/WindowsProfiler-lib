#pragma once

#include "Object.h"

#include <Windows.h>
#include <tlhelp32.h>

#include <string>

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
	 * @brief Process priority
	 */
	enum class Priority
	{
		None,
		Idle = IDLE_PRIORITY_CLASS,
		BelowNormal = BELOW_NORMAL_PRIORITY_CLASS,
		Normal = NORMAL_PRIORITY_CLASS,
		AboveNormal = ABOVE_NORMAL_PRIORITY_CLASS,
		High = HIGH_PRIORITY_CLASS,
		RealTime = REALTIME_PRIORITY_CLASS
	};

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
	 * @brief returns a process priority like a type of CPUTracker::Priority. You can convert this type to a string using
	 * Utils::Priority2String.
	 * @return std::string
	 * @param void
	 */
	Priority GetPriority() const;

private:
	HANDLE* Handle{};
	ULARGE_INTEGER LastCPU{};
	ULARGE_INTEGER LastSysCPU{};
	ULARGE_INTEGER LastUserCPU{};
};