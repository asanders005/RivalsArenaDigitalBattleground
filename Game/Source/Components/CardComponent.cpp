#include "CardComponent.h"

void CardComponent::Play()
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


void CardComponent::Read(const json_t& value)
{
	//
}

void CardComponent::Write(json_t& value)
{
	//
}
