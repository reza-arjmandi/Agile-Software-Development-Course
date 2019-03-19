#include "stdafx.h"
#include "..\Headers\Soundex.h"

std::string Soundex::Encode(const std::string & word) const
{
	if (word.empty())
	{
		return word;
	}

	return ZeroPadding(Head(word) + StrToEncodedDigit(Tail(word)));
}

std::string Soundex::Tail(const std::string & word) const
{
	if (word.length() > 1)
	{
		return word.substr(1);
	}
	return "";
}

std::string Soundex::StrToEncodedDigit(const std::string & word) const
{
	auto digitMap = std::unordered_map<char, char>{
		{ 'b', '1' },{ 'f', '1' },{ 'p', '1' },{ 'v', '1' },
	{ 'c', '2' },{ 'g', '2' },{ 'j', '2' },{ 'k', '2' },{ 'q', '2' },{ 's', '2' },{ 'x', '2' },{ 'z', '2' },
	{ 'd', '3' },{ 't', '3' },
	{ 'l', '4' },
	{ 'm', '5' },{ 'n', '5' },
	{ 'r', '6' } };

	std::string encoding;
	char previousDigit = ' ';
	if (word.length() > 0)
	{
		for (auto letter : word)
		{
			auto digit = digitMap.find(letter);
			if (digit != digitMap.end() && previousDigit != digit->second)
			{
				previousDigit = digit->second;
				encoding += digit->second;
			}
		}
	}
	return encoding;
}

std::string Soundex::Head(const std::string & word) const
{
	return std::string(1, word.front());
}

std::string Soundex::ZeroPadding(const std::string & word) const
{
	auto zerosNeeded = 4 - word.length();
	return word + std::string(zerosNeeded, '0');
}