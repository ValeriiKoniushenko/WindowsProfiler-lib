// MIT License
//
// Copyright (c) 2023 Valerii Koniushenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// 														 copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
		Sleep(100);

		Tasker.Scan();

		auto Data = Tasker.ExtrudeStatisticsFromProcesses();
		std::sort(Data.begin(), Data.end(), [](auto& a, auto& b) { return a.RAMUsage > b.RAMUsage; });
		Data.resize(10);

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