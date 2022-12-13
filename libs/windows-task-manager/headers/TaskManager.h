#pragma once

#include "RawProcess.h"

#include <unordered_map>
#include <vector>

/**
 *
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

	ContainerT::iterator begin();
	ContainerT::const_iterator begin() const;
	ContainerT::iterator end();
	ContainerT::const_iterator end() const;

private:
	ContainerT Processes;
};