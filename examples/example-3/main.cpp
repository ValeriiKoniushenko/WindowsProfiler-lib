#include "RawProcess.h"
#include <iostream>

int main()
{
	RawProcess FurMark(12144);

	std::cout << FurMark.GetStatistics().Name << std::endl;

	// As you can see we have no CPU value, we have just zero.
	// It is caused because the lib can't compare two-time deltas at the first iteration.
	// You have to call function RawProcess::Update again with small(or not) pause.
	FurMark.Update();
	std::cout << FurMark.GetStatistics().CPUUsage << std::endl; // => 0

	Sleep(100);

	FurMark.Update();
	std::cout << FurMark.GetStatistics().CPUUsage << std::endl; // => 4.43

	return 0;
}