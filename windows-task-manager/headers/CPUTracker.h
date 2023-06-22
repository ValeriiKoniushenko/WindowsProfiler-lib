// MIT License
//
// Copyright (c) 2023 Valerii Koniushenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// 														 copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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