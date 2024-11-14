#include "PlayerComponent.h"
#include "Framework/GameEventData.h"

FACTORY_REGISTER(PlayerComponent);

void PlayerComponent::Initialize()
{

	ADD_OBSERVER(PlayerDamage, PlayerComponent::OnUpdateTracker);
}

void PlayerComponent::Update(float dt)
{
}

void PlayerComponent::OnUpdateTracker(const Event& event)
{

}

void PlayerComponent::Read(const json_t& value)
{

}

void PlayerComponent::Write(json_t& value)
{
	//
}