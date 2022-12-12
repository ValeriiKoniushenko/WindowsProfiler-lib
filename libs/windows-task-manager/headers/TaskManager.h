#pragma once

#include <vector>
#include "RawProcess.h"

class TaskManager final
{
public:
	using ContainerT = std::vector<RawProcess>;

	TaskManager() = default;
	~TaskManager() = default;
	TaskManager(const TaskManager&) = delete;
	TaskManager& operator=(const TaskManager&) = delete;
	TaskManager(TaskManager&&);
	TaskManager& operator=(TaskManager&&);

	bool Scan();
	ContainerT::iterator begin();
	ContainerT::const_iterator begin() const;
	ContainerT::iterator end();
	ContainerT::const_iterator end() const;
private:
	std::vector<RawProcess> Processes;
};