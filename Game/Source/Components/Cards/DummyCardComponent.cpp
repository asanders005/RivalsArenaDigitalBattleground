#include "DummyCardComponent.h"
#include "Framework/GameEventData.h"
#include "Engine.h"

FACTORY_REGISTER(DummyCardComponent);

void DummyCardComponent::Initialize()
{
	ADD_OBSERVER(RefreshPileDisplay, DummyCardComponent::OnRefreshPileDisplay);
}

void DummyCardComponent::Update(float dt)
{
	if (owner->scene->engine->GetInput().GetMouseButtonPressed(0))
	{
		if (TextureComponent* textureComponent = owner->GetComponent<TextureComponent>())
		{
			Vector2 mousePosition = owner->scene->engine->GetInput().GetMousePosition();
			Vector2 position = owner->transform.position;

			// Check if mouse not hovering over texture
			if (mousePosition.x < position.x - ((0.5 * textureComponent->source.w) * owner->transform.scale) ||
				mousePosition.x > position.x + ((0.5 * textureComponent->source.w) * owner->transform.scale) ||
				mousePosition.y < position.y - ((0.5 * textureComponent->source.h) * owner->transform.scale) ||
				mousePosition.y > position.y + ((0.5 * textureComponent->source.h) * owner->transform.scale))
			{
				std::cout << "Dummy Card Clicked: " << m_cardName << std::endl;
				EVENT_NOTIFY_DATA(DummyCardClicked, new CardBuyEventData(m_cardName, m_tier));
				return;
			}
		}
		else
		{
			std::cerr << "Dummy Card does not contain a Texture Component" << std::endl;
		}
	}
}

void DummyCardComponent::OnRefreshPileDisplay(const Event& event)
{
	if (!isDestroyed)
	{
		isDestroyed = true;
		owner->isDestroyed = true;
	}
}

void DummyCardComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "name", m_cardName);

	std::string tier;
	READ_DATA_NAME(value, "cardTier", tier);
	if (tier == "TIER_1") m_tier = CardEnums::CardTier::TIER_1;
	else if (tier == "TIER_2") m_tier = CardEnums::CardTier::TIER_2;
	else if (tier == "HERO") m_tier = CardEnums::CardTier::HERO;
	else m_tier = CardEnums::CardTier::STARTER;
}

void DummyCardComponent::Write(json_t& value)
{
	//
}