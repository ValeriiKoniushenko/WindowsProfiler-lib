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

#pragma once

#include "CPUTracker.h"

#include <cstdlib>
#include <string>
#include <utility>

namespace Utils
{

/** @brief Describes a unit system for data storing */
enum class Unit
{
	/** Bytes */ b,
	/** Kilo Bytes */ kb,
	/** Mega Bytes */ Mb,
	/** Giga Bytes */ Gb,
	/** Terra Bytes */ Tb
};

/**
 * @brief Helps to convert a Unit(enum class) to a string
 * @return std::string - unit in the string format
 * @param Unit
 */
std::string Units2String(Unit U);

/**
 * @brief Helps to convert a bytes to kbs
 * @return double - count of kb
 * @param std::size_t - count of bites
 */
double b2kb(std::size_t Bytes);

/**
 * @brief Helps to convert a bytes to Mbs
 * @return double - count of Mb
 * @param std::size_t - count of bites
 */
double b2Mb(std::size_t Bytes);

/**
 * @brief Helps to convert a bytes to Gbs
 * @return double - count of Gb
 * @param std::size_t - count of bites
 */
double b2Gb(std::size_t Bytes);

/**
 * @brief Helps to convert a bytes to Tbs
 * @return double - count of Tb
 * @param std::size_t - count of bites
 */
double b2Tb(std::size_t Bytes);

/**
 * @brief Helps to convert a set of bytes to the fitting format. 1123byte -> 1.123kb, 2356124 -> 2.356124Mb
 * @return std::pair<double, Unit>
 * @param std::size_t - count of bites
 */
std::pair<double, Unit> b2Fit(std::size_t Bytes);

/**
 * @brief Helps to convert a set of bytes to the fitting string format. 1123byte -> 1.123kb, 2356124 -> 2.356124Mb
 * @return std::string
 * @param std::size_t - count of bites
 */
std::string b2FitString(std::size_t Bytes, bool bIsRoundOff = true);

/**
 * @brief Helps to convert a CPUTracker::Priority to std::string
 * @return std::string
 * @param CPUTracker::Priority
 */
std::string Priority2String(CPUTracker::Priority Priority);

}	 // namespace Utils