#include "DeckComponent.h"
#include "Engine.h"
#include "Framework/GameEventData.h"

#include <algorithm>
#include <iostream>
#include <typeinfo>

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
	//
}

void DeckComponent::ShuffleDraw()
{
	m_discard.push_back("card");
	m_discard.push_back("card");
	m_discard.push_back("card");
	m_discard.push_back("card3");
	m_discard.push_back("card2");
	m_discard.push_back("card2");
	m_discard.push_back("card1");
	m_discard.push_back("card1");
	m_discard.push_back("card1");

	std::vector<std::string> temp{ m_discard.begin(), m_discard.end() };

	std::shuffle(temp.begin(), temp.end(), m_rng);

	m_draw.resize(temp.size());
	std::copy(temp.begin(), temp.end(), m_draw.begin());

	std::cout << "Shuffling" << std::endl;
	for (auto card : m_draw)
	{
		std::cout << card << std::endl;
	}
	m_discard.clear();
}

void DeckComponent::OnDraw(const Event& event)
{
	//if (owner->GetComponent<PlayerComponent>().id == std::get<std::string>(event.data))
	//{
		if (m_draw.empty()) ShuffleDraw();

		std::string cardName = m_draw.back();
		m_draw.pop_back();
		m_hand.push_back(cardName);

		//auto card = Factory::Instance().Create<Actor>(cardName);
		//owner->scene->AddActor(std::move(card));

		std::cout << "Drawing Card" << std::endl;
		for (auto card : m_hand)
		{
			std::cout << card << std::endl;
		}
	//}
}

void DeckComponent::OnDiscard(const Event& event)
{
	CardNameEventData data;
	try
	{
		data = static_cast<const CardNameEventData&>(event.data);
	} 
	catch (const std::bad_cast& e)
	{
		std::cerr << "EventData type didn't match. Looking for CardNameEventData." << std::endl;
		return;
	}
		//if (owner->GetComponent<PlayerComponent>().id == data->get()->playerID)
		//{
		std::string cardName = data.cardName;
		if (!cardName.empty())
		{
			auto iter = std::find(m_hand.begin(), m_hand.end(), cardName);
			if (iter != m_hand.end())
			{
				m_hand.erase(iter);
				m_discard.push_back(cardName);
				std::cout << "Discarding: " << cardName << std::endl;
			}
			else
			{
				std::cout << "Card: " << cardName << " is not in hand\n";
			}
		}

		for (auto card : m_discard)
		{
			std::cout << card << std::endl;
		}
		//}
}

void DeckComponent::OnBuyHero(const Event& event)
{
	// Work on during Beta
	/*EventData eventData = std::get<EventData&>(event.data);
	if (CardBuyEventData data = dynamic_cast<CardBuyEventData&>(eventData))
	{

	}
	auto hero = Factory::Instance().Create<Actor>();*/
}

void DeckComponent::OnBuyConsumable(const Event& event)
{
	// Work on during Beta
}

void DeckComponent::OnUpgradeConsumable(const Event& event)
{
	// Work on during Beta
}

void DeckComponent::Read(const json_t& value)
{
	/*READ_DATA_NAME(value, "StarterConsumables", m_draw);
	READ_DATA_NAME(value, "Consumables", m_upgradesConsumable);
	READ_DATA_NAME(value, "Heroes", m_upgradesHeroes);*/
}

void DeckComponent::Write(json_t& value)
{
	//
}