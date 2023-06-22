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
