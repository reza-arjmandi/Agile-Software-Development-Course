#pragma once

class IIPConverter
{

public:
	virtual unsigned long StrToLongInt(const std::string& ipStr) const = 0;

};