#include "PlayerComponent.h"
#include "Framework/GameEventData.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Components/TextComponent.h"
#include <sstream>

FACTORY_REGISTER(PlayerComponent);

void PlayerComponent::Initialize()
{

	ADD_OBSERVER(ModifyHealth, PlayerComponent::ModifyPlayerHealth);
	ADD_OBSERVER(ModifyXP, PlayerComponent::ChangeExp);
	ADD_OBSERVER(ModifyHeroXP, PlayerComponent::ChangeHeroExp);
	ADD_OBSERVER(Reaction, PlayerComponent::React);
}

void PlayerComponent::Update(float dt)
{
	//
}

void PlayerComponent::UpdateTracker()
{
	if (auto textComp = owner->GetComponent<TextComponent>())
	{
		std::stringstream healthText;
		if (playerID.substr(0, 3) == "CPU")
		{
			healthText << "CPU Health: " << m_health;
		}
		else
		{
			healthText << "Player's Health: " << m_health;
		}
		textComp->SetText(healthText.str());
	}

}
void PlayerComponent::React(const Event& event)
{
	//Each Child Class will have one
}

void PlayerComponent::ModifyPlayerHealth(const Event& event)
{
	
	int damage = 0;
	
	if (auto eventData = dynamic_cast<const TrackerEventData*>(event.data))
	{
		if (this->playerID == eventData->targetPlayer)
		{
			damage += eventData->changeValue;

			/*if (damage <= 0)
			{
				return;
			}*/

			m_health -= damage;
			UpdateTracker();
		}
	}
}

void PlayerComponent::ChangeExp(const Event& event)
{
	auto eventData = dynamic_cast<const TrackerEventData*>(event.data);


	if (this->playerID == eventData->targetPlayer)
	{
		m_exp += eventData->changeValue;
	}
}

void PlayerComponent::ChangeHeroExp(const Event& event)
{
	auto eventData = dynamic_cast<const TrackerEventData*>(event.data);
	if (this->playerID == eventData->targetPlayer)
	{

		m_heroExp += eventData->changeValue;
	}
}


void PlayerComponent::Read(const json_t& value)
{
	PlayerComponent::Initialize();

	//Read if need
	READ_DATA(value, playerID);
	READ_DATA(value, m_health);
	READ_DATA(value, m_exp);
	READ_DATA(value, m_heroExp);
	READ_DATA(value, isActive);
	READ_DATA(value, isDied);
}

void PlayerComponent::Write(json_t& value)
{
	//you don't have to wrtie anything
}
