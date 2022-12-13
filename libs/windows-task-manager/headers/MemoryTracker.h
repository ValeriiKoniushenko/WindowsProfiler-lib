#pragma once

#include "Object.h"

#include <Windows.h>

/**
 * @brief Allows to track Memory data
 */
class MemoryTracker : public Object
{
public:
	MemoryTracker(HANDLE& Handle);
	~MemoryTracker() override;
	MemoryTracker(const MemoryTracker&) = default;
	MemoryTracker& operator=(const MemoryTracker&) = default;
	MemoryTracker(MemoryTracker&&) = default;
	MemoryTracker& operator=(MemoryTracker&&) = default;

	/**
 	 * @brief Allows to get access to the RAM usage
 	 * @return std::size_t count of bytes that now a process uses
 	 * @param void
	 */
	std::size_t RAMUsage() const;

	/**
 	 * @brief Allows to get access to the Virtual Memory usage
 	 * @return std::size_t count of bytes that now a process uses
 	 * @param void
	 */
	std::size_t VirtualMemoryUsage() const;

private:
	void ClearData() override;

private:
	HANDLE* Handle{};
};