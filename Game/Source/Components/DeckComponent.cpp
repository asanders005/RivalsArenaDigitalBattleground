#include "DeckComponent.h"
#include "Engine.h"

void DeckComponent::Initialize()
{
	ADD_OBSERVER(DrawCard, DeckComponent::OnDraw);
	ADD_OBSERVER(DiscardCard, DeckComponent::OnDiscard);
	ADD_OBSERVER(BuyHero, DeckComponent::OnBuyHero);
	ADD_OBSERVER(BuyConsumable, DeckComponent::OnBuyConsumable);
	ADD_OBSERVER(UpgradeConsumable, DeckComponent::OnUpgradeConsumable);
}

void DeckComponent::Update(float dt)
{
}

void DeckComponent::OnDraw(const Event& event)
{
}

void DeckComponent::OnDiscard(const Event& event)
{
}

void DeckComponent::OnBuyHero(const Event& event)
{
}

void DeckComponent::OnBuyConsumable(const Event& event)
{
}

void DeckComponent::OnUpgradeConsumable(const Event& event)
{
}

void DeckComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "StarterConsumables", m_draw);
	READ_DATA_NAME(value, "Consumables", m_upgradesConsumable);
	READ_DATA_NAME(value, "Heroes", m_upgradesHeroes);
}

void DeckComponent::Write(json_t& value)
{
	//
}