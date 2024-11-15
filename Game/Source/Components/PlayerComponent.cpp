#include "PlayerComponent.h"
#include "CounterComponent.h"
#include "Framework/GameEventData.h"

FACTORY_REGISTER(PlayerComponent);

void PlayerComponent::Initialize()
{
	ADD_OBSERVER(ModifyHealth, PlayerComponent::ModifyPlayerHealth);
	ADD_OBSERVER(ModifyXP, PlayerComponent::ChangeExp);
	ADD_OBSERVER(ModifyHeroXP, PlayerComponent::ChangeHeroExp);
	ADD_OBSERVER(onReaction, PlayerComponent::OnReact);
}

void PlayerComponent::Update(float dt)
{
	//
}

void PlayerComponent::OnUpdateTracker(const Event& event)
{
	//

}
void PlayerComponent::OnReact(const Event& event) 
{

	//Check if the deck with the same player id is equal
	// Then check cards that can sheild
	// Then check if the heros action or passive ability can reduce the damage

	//Ask a prompt to choose which one then dp action
	// Repeat until the user or CPU will stop.

}

void PlayerComponent::ModifyPlayerHealth(const Event& event)
{
	TrackerEventData eventData;
	int damage = 0;
	try
	{
		eventData = static_cast<const TrackerEventData&>(event.data);
	}
	catch (const std::bad_cast& e)
	{
		std::cerr << "EventData Type didn't match. Looking for DamagaeEventData." << std::endl;
		return;
	}

	if (this->id == eventData.targetPlayer)
	{
		damage = eventData.changeValue + damage;

		if (damage <= 0)
		{
			return;
		}

		m_health += damage;
	}
}

void PlayerComponent::ChangeExp(const Event& event)
{
	TrackerEventData eventData;

	try
	{
		eventData = static_cast<const TrackerEventData&>(event.data);
	}
	catch (const std::bad_cast& e)
	{
		std::cerr << "EventData Type didn't match. Looking for ExpGainEventData." << std::endl;
		return;
	}


	if(this->id == eventData.targetPlayer)
	{
		m_exp += eventData.changeValue;
	}
}

void PlayerComponent::ChangeHeroExp(const Event& event)
{
	TrackerEventData eventData;

	try
	{
		eventData = static_cast<const TrackerEventData&>(event.data);
	}
	catch (const std::bad_cast& e)
	{
		std::cerr << "EventData Type didn't match. Looking for ExpHeroGainEventData." << std::endl;
		return;
	}
	if (this->id == eventData.targetPlayer)
	{

		m_heroExp += eventData.changeValue;
	}
}


void PlayerComponent::Read(const json_t& value)
{
	PlayerComponent::Initialize();

	//Read if need
	READ_DATA(value, m_health);
	READ_DATA(value, m_exp);
	READ_DATA(value, m_heroExp);
	READ_DATA(value, id);
	READ_DATA(value, isActive);
}

void PlayerComponent::Write(json_t& value)
{
	//you don't have to wrtie anything
}
