#pragma once
#include "IIPConverter.h"

namespace Entities
{

	class IPConverter : public IIPConverter
	{

	public:
		unsigned long StrToLongInt(const std::string& ipStr) const override;

	private:
		bool HaveThreeDot(const std::string& ipStr) const;
		std::array<int, 4> SplitIPSections(const std::string& ipStr) const;
		bool IsIPSections8Bit(const std::array<int, 4>& ipSections) const;
		unsigned long IPSectionsToInt(const std::array<int, 4>& ipSections) const;

	};

}