#include "DeckComponent.h"
#include "Engine.h"

void DeckComponent::Initialize()
{
}

void DeckComponent::Update(float dt)
{
}

void DeckComponent::Read(const json_t& value)
{

	READ_DATA_NAME(value, "StarterConsumables", m_draw);
}

void DeckComponent::Write(json_t& value)
{
}