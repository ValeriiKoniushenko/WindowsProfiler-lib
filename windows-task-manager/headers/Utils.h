#pragma once

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
std::string Uits2String(Unit U);

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
std::string b2FitString(std::size_t Bytes);

}	 // namespace Utils