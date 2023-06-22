# Windows Task Manger [lib]
## ⭐ Intro
Hello everyone! If you read this page, you need one tool to get more control over your system, and this one tool, I hope, is this lib.
Just download it or clone it and connect it to your project like opensource or ```.lib\include files.```
![Animation](https://github.com/ValeriiKoniushenko/WindowsProfiler-lib/assets/99877553/f3488d64-4b54-436e-840e-f0d2ee27e17e)

## 🔧 Installation steps
1. Press the green button at the top of this page ```Code```.
2. Copy the link.
3. Open the terminal window.
4. Go to the correct directory using the command ```cd```.
5. Write ```git clone ```(don't forget about a space) and paste the link.
6. Press ```Enter```
7. Open the folder ```WindowsProfiler-lib``` using some IDE: Clion, Visual Studio, etc.
8. Compile the library using a hot-key ```Ctrl + Shift + B``` or ```Ctrl + B``` or using the build menu at the top of your screen.

## 👨‍💻 Example
More accessible examples with details can find in the folder 'example'. But now I'll try to show all abilities of this lib.
```c++
#include "TaskManager.h"
#include "Utils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setw;

void printHeader()
{
	cout << "| ";
	cout << setw(2 + 5) << "PID |";
	cout << setw(2 + 36) << "Name |";
	cout << setw(2 + 5) << "CPU |";
	cout << setw(2 + 15) << "RAM |";
	cout << setw(2 + 15) << "VRAM |";
	cout << setw(2 + 15) << "Priority |";
	cout << endl;
}

void printRow(const RawProcess::Statistics& Stat)
{
	cout << "| ";
	cout << setw(5) << Stat.PID << " |";
	cout << setw(36) << Stat.Name << " |";
	cout << setw(5) << Stat.CPUUsage << " |";
	cout << setw(15) << Utils::b2FitString(Stat.RAMUsage) << " |";
	cout << setw(15) << Utils::b2FitString(Stat.VirtualMemoryUsage) << " |";
	cout << setw(15) << Utils::Priority2String(Stat.Priority) << " |";
	cout << endl;
}

int main()
{
	TaskManager Tasker;

	cout << std::setprecision(2);

	while (1)
	{
		Sleep(1000);
		Tasker.Scan();

		auto Data = Tasker.ExtrudeStatisticsFromProcesses();
		Data.erase(std::remove_if(Data.begin(), Data.end(), [](auto& a) { return a.RAMUsage < 1024 * 1024 * 1024; }), Data.end());
		std::sort(Data.begin(), Data.end(), [](auto& a, auto& b) { return a.PID < b.PID; });

		printHeader();
		for (auto& Stat : Data)
		{
			printRow(Stat);
		}
		// => |   PID |            Name |  CPU |    RAM |    VRAM |   Priority |
		// => |   672 |          clangd |    0 |   2 Gb |    2 Gb |     Normal |
		// => | 11256 |   GoogleDriveFS |  1.3 |   1 Gb |    1 Gb |     Normal |
		// => | 11572 |         clion64 | 0.54 |   3 Gb |    3 Gb |     Normal |
	}

	return 0;
}
```

## 📞 Feedback & Contacts
You can send me e-mail: Valerii.Koniushenko@gmail.com or try to find me in telegram: @markmoran24
