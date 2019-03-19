#pragma once

class Soundex
{

public:
	std::string Encode(const std::string& word) const;

private:

	std::string Tail(const std::string& word) const;
	std::string StrToEncodedDigit(const std::string& word) const;
	std::string Head(const std::string& word) const;
	std::string ZeroPadding(const std::string& word) const;

};
