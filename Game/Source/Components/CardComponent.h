#pragma once
#include "Components/Component.h"
#include "../Framework/GameEventData.h"
#include "Event/EventManager.h"
#include <string>

class CardComponent : public Component, public Observer
{
public:
	CLASS_DECLARATION(CardComponent)
	CLASS_PROTOTYPE(CardComponent)

	void OnPlay(const Event& event);
	void OnDiscard(const Event& event);

	virtual void Ability() = 0;

	CardComponent(std::string deckID, std::string cardID) : m_deckID{ deckID }, m_cardID{ cardID } {};

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


	CardTier m_tier = CardTier::STARTER;
	PlayPhase m_phase = PlayPhase::TURN;


};