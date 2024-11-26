#include "PlayerComponent.h"
#include "Framework/GameEventData.h"

FACTORY_REGISTER(PlayerComponent);

void PlayerComponent::Initialize()
{
	ADD_OBSERVER(ModifyHealth, PlayerComponent::ModifyPlayerHealth);
	ADD_OBSERVER(ModifyXP, PlayerComponent::ChangeExp);
	ADD_OBSERVER(ModifyHeroXP, PlayerComponent::ChangeHeroExp);
	ADD_OBSERVER(Reaction, PlayerComponent::React);
	ADD_OBSERVER(CheckPlayerExp, PlayerComponent::CheckExp);
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

void PlayerComponent::CheckExp(const Event& event)
{
	if (auto data = dynamic_cast<CardBuyEventData*>(event.data))
	{
		if (data->targetPlayer == playerID)
		{
			switch (data->cardTier)
			{
			case CardEnums::CardTier::TIER_1:
				if (m_exp >= data->expReqs)
				{
					EVENT_NOTIFY_DATA(BuyCard, data);
					m_exp -= data->expReqs;
				}
				break;
			case CardEnums::CardTier::TIER_2:
				if (m_exp >= data->expReqs)
				{
					EVENT_NOTIFY_DATA(SelectUpgradeSacrifice, data);
					m_exp -= data->expReqs;
				}
				break;
			case CardEnums::CardTier::HERO:
				break;
			}
		}
	}
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
