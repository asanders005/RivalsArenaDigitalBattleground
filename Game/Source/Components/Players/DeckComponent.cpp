#include "DeckComponent.h"
#include "Engine.h"
#include "Framework/GameEventData.h"
#include "Components/Players/PlayerComponent.h"
#include "Components/UI/PileComponent.h"

#include <algorithm>
#include <iostream>
#include <typeinfo>

void DeckComponent::Initialize()
{
	/*if (auto discard = Factory::Instance().Create<Actor>("UniversalPile"))
	{
		discard->transform.position = { 50, 50 };
		discard->GetComponent<PileComponent>()->SetData(m_deckID, "PileDiscard");
		owner->scene->AddActor(std::move(discard), true);
		EVENT_NOTIFY_DATA(UpdatePileTexture, new PileTextureUpdateEventData(m_deckID, "PileDiscard", "Textures/Test.jpg"));
	}
	if (auto consumables = Factory::Instance().Create<Actor>("UniversalPile"))
	{
		consumables->transform.position = { 355, 105 };
		consumables->GetComponent<PileComponent>()->SetData(m_deckID, "PileConsumablesUpgrade");		
		owner->scene->AddActor(std::move(consumables), true);
		EVENT_NOTIFY_DATA(UpdatePileTexture, new PileTextureUpdateEventData(m_deckID, "PileConsumablesUpgrade", "Textures/Decks/" + m_deckName + "/" + m_upgradesConsumable.front() + ".png"));
	}
	if (auto heroes = Factory::Instance().Create<Actor>("UniversalPile"))
	{
		heroes->transform.position = { 655, 105 };
		heroes->GetComponent<PileComponent>()->SetData(m_deckID, "PileHeroesUpgrade");
		owner->scene->AddActor(std::move(heroes), true);
		EVENT_NOTIFY_DATA(UpdatePileTexture, new PileTextureUpdateEventData(m_deckID, "PileHeroesUpgrade", "Textures/Decks/" + m_deckName + "/" + m_upgradesHeroes.front() + ".png"));
	}*/

	ADD_OBSERVER(DrawCard, DeckComponent::OnDraw);
	ADD_OBSERVER(DiscardCard, DeckComponent::OnDiscard);

	//ADD_OBSERVER(DisplayPile, DeckComponent::OnDisplayPile);
}

void DeckComponent::Update(float dt)
{
	if (m_displayingPile != DisplayingPile::NONE)
	{

	}
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

void DeckComponent::DisplayPile(const std::string& pile)
{
	if (pile == "PileDiscard")
	{
		m_displayingPile = DisplayingPile::DISCARD;
	}
	else if (pile == "PileConsumablesUpgrade")
	{
		m_displayingPile = DisplayingPile::CONSUMABLE;
	}
	else if (pile == "PileHeroesUpgrade")
	{
		m_displayingPile = DisplayingPile::HERO;
	}

	if (m_displayingPile != DisplayingPile::NONE)
	{
		UpdateDisplayPile(0);
	}
}

void DeckComponent::UpdateDisplayPile(int index)
{
	EVENT_NOTIFY(RefreshPileDisplay);
	std::vector<std::string> temp;
	switch (m_displayingPile)
	{
	case DisplayingPile::DISCARD:
		if (!m_discard.empty())
		{
			temp.assign(m_discard.begin(), m_discard.end());
			if (m_discard.size() >= 5)
			{
				index = (index + 5 > m_discard.size()) ? m_discard.size() - 5 : (index < 0) ? 0 : index;
				for (; index < index + 5; index++)
				{
					auto card = Factory::Instance().Create<Actor>(temp[index] + "_Dummy");
					card->transform.position = { Vector2{ index * 180.0f + 70, 500.0f } };
					owner->scene->AddActor(std::move(card), true);
				}
			}
			else
			{
				for (int i = 0; i < m_discard.size(); i++)
				{
					auto card = Factory::Instance().Create<Actor>(temp[i] + "_Dummy");
					card->transform.position = { Vector2{ i * 180.0f + 70, 500.0f } };
					owner->scene->AddActor(std::move(card), true);
				}
			}
		}
		break;
	case DisplayingPile::CONSUMABLE:
		if (!m_upgradesConsumable.empty())
		{
			temp.assign(m_upgradesConsumable.begin(), m_upgradesConsumable.end());
			if (m_upgradesConsumable.size() >= 5)
			{
				index = (index + 5 > m_upgradesConsumable.size()) ? m_upgradesConsumable.size() - 5 : (index < 0) ? 0 : index;
				for (; index < index + 5; index++)
				{
					auto card = Factory::Instance().Create<Actor>(temp[index] + "_Dummy");
					card->transform.position = { Vector2{ index * 180.0f + 70, 500.0f } };
					owner->scene->AddActor(std::move(card), true);
				}
			}
			else
			{
				for (int i = 0; i < m_upgradesConsumable.size(); i++)
				{
					auto card = Factory::Instance().Create<Actor>(temp[i] + "_Dummy");
					card->transform.position = { Vector2{ i * 180.0f + 70, 500.0f } };
					owner->scene->AddActor(std::move(card), true);
				}
			}
		}
		break;
	case DisplayingPile::HERO:
		if (!m_upgradesConsumable.empty())
		{
			temp.assign(m_upgradesHeroes.begin(), m_upgradesHeroes.end());
			if (m_upgradesHeroes.size() >= 5)
			{
				index = (index + 5 > m_upgradesHeroes.size()) ? m_upgradesHeroes.size() - 5 : (index < 0) ? 0 : index;
				for (; index < index + 5; index++)
				{
					auto card = Factory::Instance().Create<Actor>(temp[index] + "_Dummy");
					card->transform.position = { Vector2{ index * 180.0f + 70, 500.0f } };
					owner->scene->AddActor(std::move(card), true);
				}
			}
			else
			{
				for (int i = 0; i < m_upgradesHeroes.size(); i++)
				{
					auto card = Factory::Instance().Create<Actor>(temp[i] + "_Dummy");
					card->transform.position = { Vector2{ i * 180.0f + 70, 500.0f } };
					owner->scene->AddActor(std::move(card), true);
				}
			}
		}
		break;
	}
}

void DeckComponent::OnDraw(const Event& event)
{
	if (!event.data) return;
	if (auto data = dynamic_cast<StringEventData*>(event.data))
	{
		if (m_deckID == data->string)
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

				if (cardID.substr(0, 3) != "CPU")
				{
					if (auto card = Factory::Instance().Create<Actor>(cardName))
					{
						card->transform.position = { Vector2{ (i - m_cardsInHand) * 180.0f + 70, 600.0f } };
						card->GetComponent<CardComponent>()->SetCardID(cardID);
						card->GetComponent<CardComponent>()->SetDeckID(m_deckID);

						owner->scene->AddActor(std::move(card), true);
						currentCard++;
						std::cout << "Drawing Card: " << cardName << std::endl;
					}
				}
			}
			m_cardsInHand = 5;
		}
	}
}

void DeckComponent::OnDiscard(const Event& event)
{
	if (!event.data) return;
	if (auto data = dynamic_cast<CardNameEventData*>(event.data))
	{
		if (m_deckID == data->deckID)
		{
			std::string cardID = data->cardID;
			if (!cardID.empty())
			{
				auto iter = std::find(m_hand.begin(), m_hand.end(), data->cardID);
				if (iter != m_hand.end())
				{
					m_hand.erase(iter);
					m_cardsInHand--;
					m_discard.push_back(data->cardName);
					std::cout << "Discarding: " << data->cardName << std::endl;
				}
				else
				{
					std::cout << "Card: " << data->cardName << " is not in hand\n";
				}
				//if (m_cardsInHand == 0) EVENT_NOTIFY_DATA(DrawCards, new StringEventData(owner->GetComponent<PlayerComponent>()->playerID));
			}

		/*for (auto card : m_discard)
		{
			std::cout << card << std::endl;
		}*/
		}
	}
}

void DeckComponent::OnDisplayPile(const Event& event)
{
	if (!event.data) return;
	if (auto data = dynamic_cast<PlayerStringEventData*>(event.data))
	{
		if (data->targetPlayer == owner->GetComponent<PlayerComponent>()->playerID)
		{
			DisplayPile(data->dataString);
		}
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