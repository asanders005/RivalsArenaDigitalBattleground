#pragma once
#include "Event/EventData.h"

#include <string>

struct GameEventData : public EventData
{
	GameEventData(std::string target) : target{ target } {}

	std::string target;
};

struct TrackerEventData : public EventData
{
	TrackerEventData(std::string targetPlayer, int changeValue) :
		targetPlayer{ targetPlayer },
		changeValue{ changeValue } 
	{}

	std::string targetPlayer;
	int changeValue = 0;
};