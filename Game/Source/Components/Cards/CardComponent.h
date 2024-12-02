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

	//Added
	std::string GetCardName() { return m_cardName; }
	std::string GetCardID() { return m_cardID; }
	void SetCardID(const std::string& cardID) { m_cardID = cardID; }
	std::string GetDeckId() { return m_deckID; }
	void SetDeckID(const std::string& deckID) { m_deckID = deckID; }
	int GetCoolDownTimer() { return m_cooldownTimer; }
	int GetCoolDown() { return m_cooldown; }
	bool GeTIsOptional() { return m_optional; }
	bool GetIsDefensive() { return m_defensive; }
	bool GetTargetPlayer() 
	{
		return !m_targetPlayer.empty();
	}
	
    CardEnums::CardTier GetCardTier() { return m_tier; }
	CardEnums::PlayPhase GetPlayPhase() { return m_phase; }
	int GetPriority() { return m_priority; }
	
	void SetProity(int priority_value) { m_priority = priority_value; }


protected:
	int m_priority = 0;

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