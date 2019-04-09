#include "pch.h"
#include "IPConverter.h"

unsigned long IPConverter::StrToLongInt(const std::string& ipStr) const
{
	if (!HaveThreeDot(ipStr))
	{
		return -1;
	}

	auto ipSections = SplitIPSections(ipStr);
	if (!IsIPSections8Bit(ipSections))
	{
		return -1;
	}

	return IPSectionsToInt(ipSections);
}

bool IPConverter::HaveThreeDot(const std::string& ipStr) const
{
	return std::count(ipStr.cbegin(), ipStr.cend(), '.') == 3;
}

std::array<int, 4> IPConverter::SplitIPSections(const std::string & ipStr) const
{
	auto stringSplitter = std::istringstream(ipStr);
	std::array<int, 4> ipSections = {-1, -1, -1, -1};
	char dotCharBuffer;
	stringSplitter >>
		ipSections[0] >> dotCharBuffer >>
		ipSections[1] >> dotCharBuffer >>
		ipSections[2] >> dotCharBuffer >>
		ipSections[3];
	return ipSections;
}

bool IPConverter::IsIPSections8Bit(const std::array<int, 4>& ipSections) const
{
	return std::all_of(ipSections.cbegin(), ipSections.cend(), [](const int& param)
	{
		return param >= 0 && param <= 255;
	});
}

unsigned long IPConverter::IPSectionsToInt(const std::array<int, 4>& ipSections) const
{
	unsigned long ipInt = 0;
	for (const auto& ipSection : ipSections)
	{
		ipInt <<= 8;
		ipInt += ipSection;
	}
	return ipInt;
}