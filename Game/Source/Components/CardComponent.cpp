#include "CardComponent.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Components/TextureComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CardComponent);

void CardComponent::Initialize()
{
  
}

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
		EVENT_NOTIFY_DATA(DiscardCard, new CardNameEventData(m_cardName, m_targetPlayer));
		owner->isDestroyed = true;
	}
}

void CardComponent::Update(float dt)
{
	if (owner->scene->engine->GetInput().GetMouseButtonPressed(0))
	{
		bool isHoveringOverCard = true;
		TextureComponent* textureComponent = owner->GetComponent<TextureComponent>();
		Vector2 mousePosition = owner->scene->engine->GetInput().GetMousePosition();
		Vector2 position = owner->transform.position;

		if (mousePosition.x < position.x - (0.5 * (textureComponent->source.w * owner->transform.scale)) ||
			mousePosition.x > position.x + (0.5 * (textureComponent->source.w * owner->transform.scale)) ||
			mousePosition.y < position.y - (0.5 * (textureComponent->source.h * owner->transform.scale)) ||
			mousePosition.y > position.y + (0.5 * (textureComponent->source.h * owner->transform.scale)))
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
	READ_DATA_NAME(value, "name", m_cardName);
	READ_DATA_NAME(value, "cooldown", m_cooldown);
	READ_DATA_NAME(value, "optional", m_optional);
	READ_DATA_NAME(value, "defensive", m_defensive);

	std::string tier = "";
	std::string phase = "";
	READ_DATA_NAME(value, "cardTier", tier);
	READ_DATA_NAME(value, "playPhase", phase);

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
