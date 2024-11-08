#pragma once
#include "Event/EventData.h"

#include <string>

struct GameEventData : public EventData
{
	GameEventData(std::string target) : target{ target } {}

	std::string target;
};