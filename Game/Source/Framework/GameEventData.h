#pragma once
#include "Event/EventData.h"

#include <string>

struct GameEventData : public EventData
{
	GameEventData(std::string target) : target{ target } {}

	std::string target;
};

struct CardBuyEventData : public EventData
{
	CardBuyEventData() = default;
	CardBuyEventData(const std::string& cardName /*Card Tier Enum rier*/) : cardName{ cardName } {}

	std::string cardName;
	// Card tier enum tier
};