#include "EString.h"
#include <algorithm>

std::string ToLower(const std::string& str)
{
	std::string lower;
	lower.resize(str.size());

	// modern c++
	std::transform(str.begin(), str.end(), lower.begin(),
		[](char c)
		{
			return std::tolower(c);
		});

	return lower;
}

std::string ToUpper(const std::string& str)
{
	std::string upper;
	upper.resize(str.size());

	// modern c++
	std::transform(str.begin(), str.end(), upper.begin(),
		[](char c)
		{
			return std::toupper(c);
		});

	return upper;
}

bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
{
	if (str1.length() != str2.length()) return false;

	return std::equal(str1.begin(), str1.end(), str2.begin(),
		[](char c1, char c2)
		{
			return std::tolower(c1) == std::tolower(c2);
		});
}
