#include "PileComponent.h"
#include "Engine.h"
#include "Framework/GameEventData.h"

void PileComponent::Initialize()
{
	ADD_OBSERVER(UpdatePileTexture, PileComponent::OnUpdateTexture);
}

void PileComponent::Update(float dt)
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
			EVENT_NOTIFY_DATA(DisplayPile, new StringEventData{ m_name });	
		}
		else
		{
			std::cerr << "Universal Pile Actor does not contain a Texture Component" << std::endl;
		}
	}
}

void PileComponent::OnUpdateTexture(const Event& event)
{
	// Use texture.UpdateTexture() to change image on pile when a card is discarded, bought, etc.
}

void PileComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "Pile_Name", m_name);
}

void PileComponent::Write(json_t& value)
{
}