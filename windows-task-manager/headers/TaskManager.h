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

#include "RawProcess.h"

#include <unordered_map>
#include <vector>

/**
 * @brief The main class for working with processes set
 */
class TaskManager final
{
public:
	using ContainerT = std::unordered_map<DWORD, RawProcess>;

	TaskManager() = default;
	~TaskManager() = default;
	TaskManager(const TaskManager&) = delete;
	TaskManager& operator=(const TaskManager&) = delete;
	TaskManager(TaskManager&&) = delete;
	TaskManager& operator=(TaskManager&&) = delete;

	/**
	 * @brief Helps to scan or rescan all processes in the Windows
	 * @param void
	 * @return bool - true if scan was successful; false - if failed.
	 */
	bool Scan();

	/**
	 * @brief Helps to get all scanned processes
	 * @param void
	 * @return ContainerT& with data
	 */
	ContainerT& GetProcesses();

	/**
	 * @brief Helps to get all scanned processes
	 * @param void
	 * @return const ContainerT& with data
	 */
	const ContainerT& GetProcesses() const;

	/**
	 * @brief Helps to extrude all Statistics from a processes
	 * @param void
	 * @return std::vector with Statistics
	 */
	std::vector<RawProcess::Statistics> ExtrudeStatisticsFromProcesses() const;

	/**
	 * @brief Needed to work with range based for. Returns an iterator to the begin
	 * @param void
	 * @return ContainerT::iterator
	 */
	ContainerT::iterator begin();

	/**
	 * @brief Needed to work with range based for. Returns a constant iterator to the begin
	 * @param void
	 * @return ContainerT::const_iterator
	 */
	ContainerT::const_iterator begin() const;

	/**
	 * @brief Needed to work with range based for. Returns an iterator to the end
	 * @param void
	 * @return ContainerT::iterator
	 */
	ContainerT::iterator end();

	/**
	 * @brief Needed to work with range based for. Returns a constant iterator to the end
	 * @param void
	 * @return ContainerT::const_iterator
	 */
	ContainerT::const_iterator end() const;

private:
	ContainerT Processes;
};