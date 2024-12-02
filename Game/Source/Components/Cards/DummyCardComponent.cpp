#include "DummyCardComponent.h"
#include "Engine.h"

FACTORY_REGISTER(DummyCardComponent);

DummyCardComponent::~DummyCardComponent()
{
	REMOVE_OBSERVER;
}

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
			if (mousePosition.x < position.x - (0.5 * (textureComponent->source.w * owner->transform.scale)) ||
				mousePosition.x > position.x + (0.5 * (textureComponent->source.w * owner->transform.scale)) ||
				mousePosition.y < position.y - (0.5 * (textureComponent->source.h * owner->transform.scale)) ||
				mousePosition.y > position.y + (0.5 * (textureComponent->source.h * owner->transform.scale)))
			{
				return;
			}
			else
			{
				std::cout << "Dummy Card Clicked: " << m_cardName << std::endl;
				EVENT_NOTIFY_DATA(DummyCardClicked, new CardBuyEventData(m_cardName, m_tier));
			}
			EVENT_NOTIFY(DummyCardClicked);
		}
		else
		{
			std::cerr << "Dummy Card does not contain a Texture Component" << std::endl;
		}
	}
}

void DummyCardComponent::OnRefreshPileDisplay(const Event& event)
{
	if (owner)
	{
		isDestroyed = true;
		owner->isDestroyed = true;
		REMOVE_OBSERVER;
	}
}

void DummyCardComponent::Read(const json_t& value)
{
	//
}

void DummyCardComponent::Write(json_t& value)
{
	//
}