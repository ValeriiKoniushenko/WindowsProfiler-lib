# Windows Task Manger [lib]
## Intro
Hello everyone! If you read this page, so you need one tool to get more control over your system, and this one tool, I hope, this lib.
Just download it or clone and connect to your project like opensource or just .lib\include files.

## Examples
More easier examples with details you can find in the folder 'example'. But now I'll try all abilities of this lib.
```c++
#include "TaskManager.h"
#include "Utils.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;

void printHeader()
{
	cout << "| ";
	cout << setw(2 + 5) << "PID |";
	cout << setw(2 + 36) << "Name |";
	cout << setw(2 + 5) << "CPU |";
	cout << setw(3 + 13) << "RAM |";
	cout << setw(3 + 13) << "VRAM |";
	cout << endl;
}

void printRow(const RawProcess::Statistics& Stat)
{
	cout << "| ";
	cout << setw(5) << Stat.PID << " |";
	cout << setw(36) << Stat.Name << " |";
	cout << setw(5) << Stat.CPUUsage << " |";
	auto RAM = Utils::b2Fit(Stat.RAMUsage);
	cout << setw(10) << RAM.first << " " << setw(3) << Utils::Uits2String(RAM.second) << " |";
	auto VRAM = Utils::b2Fit(Stat.VirtualMemoryUsage);
	cout << setw(10) << VRAM.first << " " << setw(3) << Utils::Uits2String(VRAM.second) << " |";
	cout << endl;
}

int main()
{
	TaskManager Tasker;

	cout << std::setprecision(2);

	while(1)
	{
		Sleep(1000);
		Tasker.Scan();

		auto Data = Tasker.ExtrudeStatisticsFromProcesses();
		std::remove_if(Data.begin(), Data.end(), [](auto& a) { return a.CPUUsage == 0.; });
		std::sort(Data.begin(), Data.end(), [](auto& a, auto& b) { return a.PID < b.PID; });
		Data.resize(10);
		for (auto& Stat : Data)
		{
			printRow(Stat);
		}
		// => |   960 |                          fsnotifier |    0 |       2.7  Mb |   5.4e+02  kb |
		// => |  1056 |                         nvcontainer |    0 |        67  Mb |        46  Mb |
		// => |  1088 |             StartMenuExperienceHost |    0 |        74  Mb |        24  Mb |
		// => |  2092 |                       RuntimeBroker |    0 |        19  Mb |       3.8  Mb |
		// => |  2328 |                       TextInputHost |    0 |        54  Mb |        35  Mb |
		// => |  3100 |                             conhost |    0 |        17  Mb |       7.3  Mb |
		// => |  3200 |                       GoogleDriveFS |    0 |        27  Mb |        13  Mb |
		// => |  3624 |                       GoogleDriveFS |    0 |     1e+02  Mb |        54  Mb |
		// => |  3828 |                        NVIDIA Share |    0 |        81  Mb |        55  Mb |
		// => |  4028 |                      ProcessManager |  1.8 |        45  Mb |        37  Mb |
	}

	return 0;
}
```

## Feedback & Contacts
You can send me e-mail: Valerii.Koniushenko@gmail.com or try to find me in telegram: @markmoran24