#include "DiscardCardComponent.h"
#include "Engine.h"

void DiscardCardComponent::Initialize()
{
	ADD_OBSERVER(DiscardCard, DiscardCardComponent::OnOtherCardDiscard);
}

void DiscardCardComponent::Update(float dt)
{
}

void DiscardCardComponent::Ability()
{
}

void DiscardCardComponent::OnOtherCardDiscard(const Event& event)
{
	if (auto data = dynamic_cast<CardNameEventData*>(event.data))
	{
		if (m_deckID == data->deckID)
		{
			
		}
		delete data;
	}
}





void DiscardCardComponent::Read(const json_t& value)
{
}

void DiscardCardComponent::Write(json_t& value)
{
}
