#pragma once
#include "Event/Event.h"

#include <string>

struct TargetEventData : public EventData
{
	TargetEventData(std::string targetPlayer) : targetPlayer{ targetPlayer } {}

	std::string targetPlayer;
};

struct CardNameEventData : public EventData
{
	CardNameEventData() = default;
	CardNameEventData(const std::string& cardName, const std::string& targetPlayer) :
		cardName{ cardName },
		targetPlayer{ targetPlayer }
	{}

	std::string targetPlayer;
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