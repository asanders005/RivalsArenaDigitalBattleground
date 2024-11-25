#include "ButtonComponent.h"
#include "Engine.h"
#include "Framework/GameEventData.h"

FACTORY_REGISTER(ButtonComponent);

void ButtonComponent::Initialize()
{
	ADD_OBSERVER(DisplayButton, ButtonComponent::OnDisplayUpdate);
}

void ButtonComponent::Update(float dt)
{
	if (owner->scene->engine->GetInput().GetMouseButtonPressed(0))
	{
		bool mouseOver = true;
		TextureComponent* textureComponent = owner->GetComponent<TextureComponent>();
		Vector2 mousePosition = owner->scene->engine->GetInput().GetMousePosition();
		Vector2 position = owner->transform.position;

		if (mousePosition.x < position.x - (0.5 * (textureComponent->source.w * owner->transform.scale)) ||
			mousePosition.x > position.x + (0.5 * (textureComponent->source.w * owner->transform.scale)) ||
			mousePosition.y < position.y - (0.5 * (textureComponent->source.h * owner->transform.scale)) ||
			mousePosition.y > position.y + (0.5 * (textureComponent->source.h * owner->transform.scale)))
		{
			mouseOver = false;
		}
		
		if (mouseOver)
		{
			std::cout << buttonID << " Clicked" << std::endl;
			EVENT_NOTIFY_DATA(ButtonClicked, new StringEventData(buttonID));
		}
	}
}

void ButtonComponent::OnDisplayUpdate(const Event& event)
{
	if (auto data = dynamic_cast<StringBoolEventData*>(event.data))
	{
		if (data->string == buttonID)
		{
			if (data->_bool)
			{
				owner->Activate();
			}
			else
			{
				owner->Deactivate();
			}
		}
	}
}

void ButtonComponent::Read(const json_t& value)
{
}

void ButtonComponent::Write(json_t& value)
{
}