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