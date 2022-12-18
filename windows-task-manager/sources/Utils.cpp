#include "Utils.h"

namespace Utils
{

std::string Units2String(Unit U)
{
	if (U == Unit::b)
	{
		return {"b"};
	}
	if (U == Unit::kb)
	{
		return {"kb"};
	}
	if (U == Unit::Mb)
	{
		return {"Mb"};
	}
	if (U == Unit::Gb)
	{
		return {"Gb"};
	}
	if (U == Unit::Tb)
	{
		return {"Tb"};
	}

	return {"None"};
}

double b2kb(std::size_t Bytes)
{
	return static_cast<double>(Bytes) / 1024.;
}

double b2Mb(std::size_t Bytes)
{
	return static_cast<double>(Bytes) / (1024. * 1024.);
}

double b2Gb(std::size_t Bytes)
{
	return static_cast<double>(Bytes) / (1024. * 1024. * 1024.);
}

double b2Tb(std::size_t Bytes)
{
	return static_cast<double>(Bytes) / (1024. * 1024. * 1024. * 1024.);
}

std::pair<double, Unit> b2Fit(std::size_t Bytes)
{
	double result = Bytes;
	int Units = 0;
	while (result > 1000.)
	{
		result /= 1000., Units++;
	}

	return {result, static_cast<Unit>(Units)};
}

std::string b2FitString(std::size_t Bytes, bool bIsRoundOff)
{
	auto Data = b2Fit(Bytes);
	if (bIsRoundOff)
	{
		return std::to_string(static_cast<std::size_t>(Data.first)) + " " + Units2String(Data.second);
	}

	return std::to_string(Data.first) + " " + Units2String(Data.second);
}

std::string Priority2String(CPUTracker::Priority Priority)
{
	switch (Priority)
	{
		case CPUTracker::Priority::Idle:
			return "Idle";
		case CPUTracker::Priority::BelowNormal:
			return "Below normal";
		case CPUTracker::Priority::Normal:
			return "Normal";
		case CPUTracker::Priority::AboveNormal:
			return "Above normal";
		case CPUTracker::Priority::High:
			return "High";
		case CPUTracker::Priority::RealTime:
			return "Real Time";
	}
	return "None";
}

}	 // namespace Utils