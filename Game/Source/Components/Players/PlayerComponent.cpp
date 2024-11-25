#include "PlayerComponent.h"
#include "Framework/GameEventData.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"

FACTORY_REGISTER(PlayerComponent);

void PlayerComponent::Initialize()
{
	if (auto player = Factory::Instance().Create<Actor>(playerID))
	{
		this->owner->scene->AddActor(std::move(player), true);

	}

	ADD_OBSERVER(ModifyHealth, PlayerComponent::ModifyPlayerHealth);
	ADD_OBSERVER(ModifyXP, PlayerComponent::ChangeExp);
	ADD_OBSERVER(ModifyHeroXP, PlayerComponent::ChangeHeroExp);
	ADD_OBSERVER(Reaction, PlayerComponent::React);
}

void PlayerComponent::Update(float dt)
{
	//
}

void PlayerComponent::OnUpdateTracker(const Event& event)
{
	//

}
void PlayerComponent::React(const Event& event)
{
	//Each Child Class will have one
}

void PlayerComponent::ModifyPlayerHealth(const Event& event)
{
	
	int damage = 0;
	
	auto eventData = dynamic_cast<const TrackerEventData*>(event.data);
	
	
	if (this->playerID == eventData->targetPlayer)
	{
		damage = eventData->changeValue + damage;

		if (damage <= 0)
		{
			return;
		}

		m_health += damage;
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
