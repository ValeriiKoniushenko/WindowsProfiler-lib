#include "MemoryTracker.h"

#include <psapi.h>

std::size_t MemoryTracker::RAMUsage() const
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(*Handle, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

	return static_cast<std::size_t>(pmc.WorkingSetSize);
}

std::size_t MemoryTracker::VirtualMemoryUsage() const
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(*Handle, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

	return static_cast<std::size_t>(pmc.PrivateUsage);
}

void MemoryTracker::ClearData()
{
	Handle = {};
}

MemoryTracker::MemoryTracker(HANDLE& Handle) :
	Handle(&Handle)
{
}

MemoryTracker::~MemoryTracker()
{
	ClearData();
}
