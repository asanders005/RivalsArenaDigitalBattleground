#pragma once
#include "Components/Component.h"
#include <string>

class CardComponent : public Component
{
public:
	CLASS_DECLARATION(CardComponent)
	CLASS_PROTOTYPE(CardComponent)

	virtual void Play()
	{
		if (!m_defensive) {
			// choose between players to play against
		}
		// else m_targetplayer = the player

		if (m_cooldownTimer == 0)
		{
			m_cooldownTimer = m_cooldown;
		}
	}

public:
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

protected:
	std::string m_cardName;
	int m_cooldownTimer = 0;
	int m_cooldown = 0;
	bool m_optional = false;
	bool m_defensive = false;
	std::string m_targetPlayer;

};