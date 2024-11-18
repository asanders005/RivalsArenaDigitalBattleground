#pragma once
#include "Event/EventData.h"

#include <string>

struct StringEventData : public EventData
{
	StringEventData() = default;
	StringEventData(const std::string& string) : string{ string } {}

	std::string string;
};

struct CardNameEventData : public EventData
{
	CardNameEventData() = default;
	CardNameEventData(const std::string& cardID, const std::string& cardName) :
		cardID{ cardID },
		cardName{ cardName } 
	{}

	std::string cardID;
	std::string cardName;
};

struct CardBuyEventData : public EventData
{
	CardBuyEventData() = default;
	CardBuyEventData(const std::string& cardName /*Card Tier Enum rier*/) : cardName{ cardName } {}

	std::string cardName;
	// Card tier enum tier
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