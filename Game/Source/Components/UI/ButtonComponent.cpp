#include "ButtonComponent.h"
#include "Engine.h"
#include "Framework/GameEventData.h"
#include <Components/Players/CPUComponent.h>

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

		if (buttonID == "CPUHealthButton")
		{
			ShowCPUHealth();
		}
		else if (buttonID == "PlayerHealthButton")
		{
			ShowPlayerHealth();
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

 void ButtonComponent::ShowCPUHealth()
{
	 auto& listofcards = owner->scene->actors;

	 std::string health;

	 for (auto& actors : owner->scene->actors)
	 {
		 if (actors.get()->GetComponent<CPUComponent>())
		 {
			 health = actors.get()->GetComponent<CPUComponent>()->GetHealth();
		 }
	 }

	 //TextComponent::TextComponent(const TextComponent & other)
	 //{
		// text = other.text;
		// fontName = other.fontName;
		// fontSize = other.fontSize;
		// color = other.color;

		// textChanged = true;
		// m_text = std::make_unique<Text>(*other.m_text);
	 //}
	 //TextComponent textcomp = std::make_unique<TextComponent>();

	 //owner->AddComponent(std::make_unique<TextComponent>())

	//if (!cpuComponent.empty())
	//{
	//	std::cout << "CPU Health: " << cpuComponent.front()->GetHealth() << std::endl;
	//}
	//else
	//{
	//	std::cerr << "CPU Component not found!" << std::endl;
	//}
}

void ButtonComponent::ShowPlayerHealth()
{
	//auto playerComponent = owner->scene->GetActors<PlayerComponent>();

	//if (!playerComponent.empty())
	//{
	//	std::cout << "Player Health: " << playerComponent.front()->GetHealth() << std::endl;
	//}
	//else
	//{
	//	std::cerr << "Player Component not found!" << std::endl;
	//}
}