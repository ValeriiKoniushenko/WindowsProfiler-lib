#include "RawProcess.h"
#include <iostream>

int main()
{
	RawProcess FurMark(12144);
	FurMark.Update();
	std::cout << FurMark.GetStatistics() << std::endl;
	// => { PID: 12144, Name: cpuburner, CPU Usage: 0, RAM Usage: 19185664, Virtual Memory Usage: 26144768,
	// =>   Path: C:\Program Files(x86)\Geeks3D\Benchmarks\FurMark\cpuburner.exe }
	return 0;
}