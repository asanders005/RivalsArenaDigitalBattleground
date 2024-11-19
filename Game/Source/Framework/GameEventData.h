#pragma once
#include "Event/EventData.h"
#include "../Components/CardComponent.h"

#include <string>

struct TargetEventData : public EventData
{
	TargetEventData() = default;
	TargetEventData(const std::string& targetPlayer) : targetPlayer{ targetPlayer } {}

	std::string targetPlayer;
};

struct CardNameEventData : public EventData
{
	CardNameEventData() = default;
	CardNameEventData(const std::string& cardName, const std::string& targetPlayer, const std::string& deckID) :
		cardName{ cardName },
		targetPlayer{ targetPlayer },
		deckID{ deckID }
	{}

	std::string targetPlayer;
	std::string cardName;
	std::string deckID;
};

struct CardIDEventData : public EventData
{
	CardIDEventData() = default;
	CardIDEventData(const std::string& cardID) :
		cardID{ cardID }
	{}

	std::string cardID;
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

struct CardPhaseInfoEventData : public EventData
{
	CardPhaseInfoEventData() = default;
	CardPhaseInfoEventData(const std::string& cardId, const CardComponent::PlayPhase& playPhase) :
		cardId{ cardId },
		deckId{ deckId }
	{}

	std::string cardId;
	std::string deckId;
};