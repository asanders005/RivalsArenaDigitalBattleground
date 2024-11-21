#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"
#include <string>

namespace CardEnums
{
	enum class CardTier : char
	{
		STARTER,
		TIER_1,
		TIER_2,
		HERO
	};

	enum class PlayPhase : char
	{
		START_OF_TURN,
		TURN,
		END_OF_TURN,
		PASSIVE,
		REACTION,
	};

	enum class Tracker
	{
		HEALTH,
		XP,
		HERO_XP,
		GIMMICK
	};
}

class CardComponent : public Component, public Observer
{
public:
	CLASS_DECLARATION(CardComponent)

	void OnPlay(const Event& event);
	void OnDiscard(const Event& event);

	virtual void Ability() = 0;

	CardComponent() = default;
	CardComponent(std::string deckID, std::string cardID) : m_deckID{ deckID }, m_cardID{ cardID } {};

	void Initialize() override;


	void Update(float dt) override;

protected:

	void DiscardCard();

	std::string m_cardName;
	int m_cooldownTimer = 0;
	int m_cooldown = 0;
	bool m_optional = false;
	bool m_defensive = false;
	std::string m_targetPlayer;
	std::string m_deckID;
	std::string m_cardID;


	CardEnums::CardTier m_tier = CardEnums::CardTier::STARTER;
	CardEnums::PlayPhase m_phase = CardEnums::PlayPhase::TURN;


};