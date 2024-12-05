#pragma once
#include "Event/EventData.h"
#include "Components/Cards/CardComponent.h"

#include <string>

struct StringEventData : public EventData
{
	StringEventData() = default;
	StringEventData(const std::string& string) : string{ string } {}

	std::string string;
};

struct StringBoolEventData : public EventData
{
	StringBoolEventData(const std::string& string, bool _bool) :
		string{ string },
		_bool{ _bool }
	{}

	std::string string;
	bool _bool;
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
	CardNameEventData(const std::string& cardID, const std::string& cardName, const std::string& deckID) :
		cardID{ cardID },
		cardName{ cardName },
		deckID{ deckID }
	{}

	std::string cardID;
	std::string cardName;
	std::string deckID;
};

struct CardDeckIDEventData : public EventData
{
	CardDeckIDEventData(const std::string& cardID, const std::string& deckID) :
		cardID{ cardID },
		deckID{ deckID }
	{}

	std::string cardID;
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
	CardBuyEventData(const std::string& cardName /*::CardTier cardTier*/) : cardName{ cardName }/*, cardTier{ cardTier }*/ {}

	std::string cardName;
	//CardTier cardTier;
};

struct TrackerEventData : public EventData
{
	TrackerEventData(const std::string& targetPlayer, int changeValue, bool roundUp = false) :
		targetPlayer{ targetPlayer },
		changeValue{ (float) changeValue },
		roundUp{ roundUp }
	{}

	TrackerEventData(const std::string& targetPlayer, float changeValue, bool roundUp = false) :
		targetPlayer{ targetPlayer },
		changeValue{ changeValue },
		roundUp{ roundUp }
	{}

	std::string cardID;
	std::string targetPlayer;
	float changeValue = 0;
	bool roundUp = false;
};

struct PointSpendingQueryEventData : public EventData
{
	PointSpendingQueryEventData(std::string targetPlayer, std::string cardID, int changeValue, CardEnums::Tracker trackerModifying) :
		targetPlayer{ targetPlayer },
		cardID{ cardID },
		changeValue{ changeValue },
		trackerModifying{ trackerModifying }
	{}

	std::string targetPlayer;
	std::string cardID;
	int changeValue;
	CardEnums::Tracker trackerModifying;
};

struct CardPhaseInfoEventData : public EventData
{
	CardPhaseInfoEventData() = default;
	CardPhaseInfoEventData(const std::string& cardId, const CardEnums::PlayPhase& playPhase) :
		cardId{ cardId },
		phase{ playPhase }
	{}

	std::string cardId;
	CardEnums::PlayPhase phase;
};