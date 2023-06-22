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