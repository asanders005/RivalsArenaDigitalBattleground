#pragma once
#include "Components/Component.h"
#include "../Framework/GameEventData.h"
#include "Event/EventManager.h"
#include <string>

class CardComponent : public Component
{
public:
	CLASS_DECLARATION(CardComponent)
	CLASS_PROTOTYPE(CardComponent)

	virtual void Play();

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

	void Initialize() override;


	void Update(float dt) override;

protected:
	std::string m_cardName;
	int m_cooldownTimer = 0;
	int m_cooldown = 0;
	bool m_optional = false;
	bool m_defensive = false;
	std::string m_targetPlayer;


	CardTier m_tier;
	PlayPhase m_phase;


};