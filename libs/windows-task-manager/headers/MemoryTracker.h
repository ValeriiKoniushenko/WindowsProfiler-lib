#pragma once

#include "Object.h"

#include <Windows.h>

class MemoryTracker : public Object
{
public:
	MemoryTracker(HANDLE& Handle);
	~MemoryTracker() override;
	MemoryTracker(const MemoryTracker&) = default;
	MemoryTracker& operator=(const MemoryTracker&) = default;
	MemoryTracker(MemoryTracker&&) = default;
	MemoryTracker& operator=(MemoryTracker&&) = default;

	std::size_t RAMUsage() const;
	std::size_t VirtualMemoryUsage() const;

private:
	void ClearData() override;

private:
	HANDLE* Handle{};
};