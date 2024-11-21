#pragma once
#include "Event/EventData.h"
#include "Components/CardComponent.h"

#include <string>

struct StringEventData : public EventData
{
	StringEventData() = default;
	StringEventData(const std::string& string) : string{ string } {}

	std::string string;
};

struct PlayerStringEventData : public EventData
{
	PlayerStringEventData(const std::string& targetPlayer, const std::string& dataString) :
		targetPlayer{ targetPlayer },
		dataString{ dataString }
	{}

	std::string targetPlayer;
	std::string dataString;
};

struct PileTextureUpdateEventData : public EventData
{
	PileTextureUpdateEventData(const std::string& targetPlayer, const std::string& targetPile, const std::string& textureName) :
		targetPlayer{ targetPlayer },
		targetPile{ targetPile },
		textureName{ textureName }
	{}

	std::string targetPlayer;
	std::string targetPile;
	std::string textureName;
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
	CardBuyEventData(const std::string& cardName /*CardComponent::CardTier cardTier*/) : cardName{ cardName }/*, cardTier{ cardTier }*/ {}

	std::string cardName;
	//CardComponent::CardTier cardTier;
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