#include "CardComponent.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Components/TextureComponent.h"
#include "Engine.h"

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
	if (m_tier != CardTier::HERO)
	{
		EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData(m_cardName, m_targetPlayer));
		owner->isDestroyed = true;
	}
}

void CardComponent::Update(float dt)
{
	if (owner->scene->engine->GetInput().GetMouseButtonPressed(0))
	{
		bool isHoveringOverCard;
		TextureComponent* textureComponent = owner->GetComponent<TextureComponent>();
		Vector2 mousePosition = owner->scene->engine->GetInput().GetMousePosition();
		Vector2 position = owner->transform.position;

		if (mousePosition.x < position.x - (0.5 * textureComponent->source.w) ||
			mousePosition.x > position.x + (0.5 * textureComponent->source.w) ||
			mousePosition.y < position.y - (0.5 * textureComponent->source.h) ||
			mousePosition.y > position.y + (0.5 * textureComponent->source.h))
		{
			isHoveringOverCard = false;
		}

		if (isHoveringOverCard)
		{
			Play();
		}
	}
}


void CardComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "Name", m_cardName);
	READ_DATA_NAME(value, "Cooldown", m_cooldown);
	READ_DATA_NAME(value, "Optional", m_optional);
	READ_DATA_NAME(value, "Defensive", m_defensive);

	std::string tier = "";
	std::string phase = "";
	READ_DATA_NAME(value, "CardTier", tier);
	READ_DATA_NAME(value, "PlayPhase", phase);

	if (tier == "TIER_1") m_tier = CardTier::TIER_1;
	else if (tier == "TIER_2") m_tier = CardTier::TIER_2;
	else if (tier == "HERO") m_tier = CardTier::HERO;
	else m_tier = CardTier::STARTER;

	if (phase == "START_OF_TURN") m_phase = PlayPhase::START_OF_TURN;
	else if (phase == "END_OF_TURN") m_phase = PlayPhase::END_OF_TURN;
	else if (phase == "PASSIVE") m_phase = PlayPhase::PASSIVE;
	else if (phase == "REACTION") m_phase = PlayPhase::REACTION;
	else m_phase = PlayPhase::TURN;
}

void CardComponent::Write(json_t& value)
{
	//
}
