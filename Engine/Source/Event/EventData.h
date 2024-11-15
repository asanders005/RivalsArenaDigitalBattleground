#pragma once
#include <string>

struct EventData
{
	EventData() = default;
	virtual ~EventData() = default;
	
	std::string dataName = "data";
};