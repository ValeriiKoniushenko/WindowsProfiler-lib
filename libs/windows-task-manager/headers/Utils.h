#pragma once

#include <cstdlib>
#include <utility>
#include <string>

namespace Utils
{

enum class Unit
{
	b,
	kb,
	Mb,
	Gb,
	Tb
};

std::string Uits2String(Unit U);
double b2kb(std::size_t Bytes);
double b2Mb(std::size_t Bytes);
double b2Gb(std::size_t Bytes);
double b2Tb(std::size_t Bytes);
std::pair<double, Unit> b2Fit(std::size_t Bytes);

}	// namespace Utils