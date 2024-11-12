#include "DeckComponent.h"
#include "Engine.h"
#include "Framework/GameEventData.h"
#include <algorithm>
#include <iostream>

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

void DeckComponent::ShuffleDraw()
{
	std::shuffle(std::begin(m_discard), std::end(m_discard), m_rng);

	m_draw.resize(m_discard.size());
	m_draw = m_discard;
	for (auto card : m_draw)
	{
		std::cout << card << std::endl;
	}
	m_discard.clear();
}

void DeckComponent::OnDraw(const Event& event)
{
	std::string cardName = m_draw.back();
	m_draw.pop_back();
	m_hand.push_back(cardName);
	auto card = Factory::Instance().Create<Actor>(cardName);

	owner->scene->AddActor(std::move(card));
}

void DeckComponent::OnDiscard(const Event& event)
{

}

void DeckComponent::OnBuyHero(const Event& event)
{
	EventData eventData = std::get<EventData&>(event.data);
	if (CardBuyEventData data = dynamic_cast<CardBuyEventData&>(eventData))
	{

	}
	auto hero = Factory::Instance().Create<Actor>();
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