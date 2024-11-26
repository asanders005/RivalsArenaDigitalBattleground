#pragma once
#include "Components/Component.h"

#include "Event/EventManager.h"
#include "rapidjson/document.h"
#include <random>

class DeckComponent : public Component, public Observer
{
public:
	struct DeckData
	{
		std::vector<std::string> starter;
		std::vector<std::string> tier1;
		std::vector<std::string> tier2;
		std::vector<std::string> hero;
	};
	CLASS_DECLARATION(DeckComponent)
	CLASS_PROTOTYPE(DeckComponent)

	DeckComponent(std::string id) : m_deckID{ id } {}

	void Initialize() override;

	void Update(float dt) override;

	// Events
	void OnDraw(const Event& event);
	void OnDiscard(const Event& event);
	void OnBuyHero(const Event& event);
	void OnBuyConsumable(const Event& event);
	void OnUpgradeConsumable(const Event& event);

	void OnDisplayPile(const Event& event);

	std::list<std::string> GetHand() { return m_hand; }
	std::list<std::string> GetHeroes() { return m_heroes; }
	std::list<std::string> GetUpgradeConsumables() { return m_upgradesConsumable; }
	std::list<std::string> GetUpgradeHeroes() { return m_upgradesHeroes; }


private:
	void ShuffleDraw();

	void DisplayPile(const std::string& pile);
	void UpdateDisplayPile(int index);

private:
	enum class DisplayingPile
	{
		NONE,
		DISCARD,
		CONSUMABLE,
		HERO
	};

private:
	std::string m_deckID;
	std::string m_deckName;

	// Vectors containing strings to create cards from
	int m_cardsInHand = 0;
	std::list<std::string> m_draw;
	std::list<std::string> m_hand;
	std::list<std::string> m_discard;
	std::list<std::string> m_heroes;
	std::list<std::string> m_upgradesConsumable;
	std::list<std::string> m_upgradesHeroes;

	DisplayingPile m_displayingPile = DisplayingPile::NONE;

	std::default_random_engine m_rng = std::default_random_engine{ (unsigned int)time(0) };
	void BuyCard(const std::string& cardName);
};