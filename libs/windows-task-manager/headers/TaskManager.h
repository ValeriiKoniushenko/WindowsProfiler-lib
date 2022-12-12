#pragma once

#include <vector>
#include "RawProcess.h"

class TaskManager final
{
public:
	TaskManager() = default;
	~TaskManager() = default;
	TaskManager(const TaskManager&) = delete;
	TaskManager& operator=(const TaskManager&) = delete;
	TaskManager(TaskManager&&);
	TaskManager& operator=(TaskManager&&);

	bool Scan();

private:
	std::vector<RawProcess> Processes;
};