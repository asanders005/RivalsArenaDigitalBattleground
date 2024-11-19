#include "DeckComponent.h"
#include "Engine.h"
#include "Framework/GameEventData.h"
#include "Components/PlayerComponent.h"
#include "Components/PileComponent.h"

#include <algorithm>
#include <iostream>
#include <typeinfo>

void DeckComponent::Initialize()
{
	auto discard = Factory::Instance().Create<Actor>("UniversalPile");
	//discard->transform.position = ;
	discard->GetComponent<PileComponent>()->SetData(m_deckID, "PileDiscard");
	owner->scene->AddActor(std::move(discard), true);
	auto consumables = Factory::Instance().Create<Actor>("UniversalPile");
	//consumables->transform.position = ;
	consumables->GetComponent<PileComponent>()->SetData(m_deckID, "PileDiscard");
	consumables->GetComponent<PileComponent>()->UpdateTexture("Textures/Decks/" + m_deckName + "/" + m_upgradesConsumable.front() + ".png");
	owner->scene->AddActor(std::move(consumables), true);
	auto heroes = Factory::Instance().Create<Actor>("UniversalPile");
	//heroes->transform.position = ;
	heroes->GetComponent<PileComponent>()->SetData(m_deckID, "PileDiscard");
	heroes->GetComponent<PileComponent>()->UpdateTexture("Textures/Decks/" + m_deckName + "/" + m_upgradesHeroes.front() + ".png");
	owner->scene->AddActor(std::move(heroes), true);

	ADD_OBSERVER(DrawCards, DeckComponent::OnDraw);
	ADD_OBSERVER(DiscardCard, DeckComponent::OnDiscard);
	ADD_OBSERVER(BuyHero, DeckComponent::OnBuyHero);
	ADD_OBSERVER(BuyConsumable, DeckComponent::OnBuyConsumable);
	ADD_OBSERVER(UpgradeConsumable, DeckComponent::OnUpgradeConsumable);

	ADD_OBSERVER(DisplayPile, DeckComponent::OnDisplayPile);
}

void DeckComponent::Update(float dt)
{
	//
}

void DeckComponent::ShuffleDraw()
{
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
	if (auto data = dynamic_cast<StringEventData*>(event.data))
	{
		if (owner->GetComponent<PlayerComponent>()->playerID == data->string)
		{

			int currentCard = m_cardsInHand + 1;
			for (int i = 5; i > m_cardsInHand; i--)
			{
				if (m_draw.empty()) ShuffleDraw();
				std::string cardName = m_draw.back();

				std::string cardID;
				bool containsID = true;
				do
				{
					int idNum = random(10);
					cardID = m_deckID + "_Card" + std::to_string(idNum);
					auto iter = std::find(m_hand.begin(), m_hand.end(), cardID);
					if (iter == m_hand.end()) containsID = false;
				} while (containsID);
				m_draw.pop_back();
				m_hand.push_back(cardID);

				auto card = Factory::Instance().Create<Actor>(cardName);
				card->transform.position = { Vector2{ i * 180.0f + 70, 600.0f } };
				owner->scene->AddActor(std::move(card), true);
				currentCard++;
				std::cout << "Drawing Card: " << cardName << std::endl;
			}
			m_cardsInHand = 5;
		}
		delete data;
	}
}

void DeckComponent::OnDiscard(const Event& event)
{
	if (auto data = dynamic_cast<CardNameEventData*>(event.data))
	{
		//if (owner->GetComponent<PlayerComponent>().id == data->get()->playerID)
		//{
		std::string cardID = data->cardName;
		if (!cardID.empty())
		{
			auto iter = std::find(m_hand.begin(), m_hand.end(), cardID);
			if (iter != m_hand.end())
			{
				m_hand.erase(iter);
				m_cardsInHand--;
				m_discard.push_back(cardID);
				std::cout << "Discarding: " << cardID << std::endl;
			}
			else
			{
				std::cout << "Card: " << cardID << " is not in hand\n";
			}
			if (m_cardsInHand == 0) EVENT_NOTIFY_DATA(DrawCards, new StringEventData(owner->GetComponent<PlayerComponent>()->playerID));
		}

		/*for (auto card : m_discard)
		{
			std::cout << card << std::endl;
		}*/
		//}
		delete data;
	}
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

void DeckComponent::OnDisplayPile(const Event& event)
{
	if (auto data = dynamic_cast<PlayerStringEventData*>(event.data))
	{
		if (data->targetPlayer == owner->GetComponent<PlayerComponent>()->playerID)
		{
			
		}
		delete data;
	}
}

void DeckComponent::Read(const json_t& value)
{
    DeckData deck;
    READ_DATA_NAME(value.FindMember("deck")->value.GetObject(),"name", m_deckName);
    READ_DATA_NAME(value.FindMember("deck")->value.GetObject(),"starter", deck.starter);
    READ_DATA_NAME(value.FindMember("deck")->value.GetObject(),"tier1", deck.tier1);
    READ_DATA_NAME(value.FindMember("deck")->value.GetObject(),"tier2", deck.tier2);
    READ_DATA_NAME(value.FindMember("deck")->value.GetObject(),"hero", deck.hero);
    for ( const auto& e : deck.starter)
    {
        m_draw.push_back(e);
    }
    for ( const auto& e : deck.tier1)
    {
        m_upgradesConsumable.push_back(e);
    }
    for ( const auto& e : deck.tier2)
    {
        m_upgradesConsumable.push_back(e);
    }
    for ( const auto& e : deck.hero)
    {
        m_upgradesHeroes.push_back(e);
    }
}

void DeckComponent::Write(json_t& value)
{
	//
}