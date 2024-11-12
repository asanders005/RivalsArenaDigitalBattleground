#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"
#include <random>

class DeckComponent : public Component, public Observer
{
public:
	CLASS_DECLARATION(DeckComponent)
	CLASS_PROTOTYPE(DeckComponent)

	void Initialize() override;

	void Update(float dt) override;

	void ShuffleDraw();

	// Events
	void OnDraw(const Event& event);
	void OnDiscard(const Event& event);
	void OnBuyHero(const Event& event);
	void OnBuyConsumable(const Event& event);
	void OnUpgradeConsumable(const Event& event);

private:
	// Vectors containing strings to create cards from
	int m_cardsInHand = 0;
	std::list<std::string> m_draw;
	std::list<std::string> m_hand;
	std::list<std::string> m_discard;
	std::list<std::string> m_upgradesConsumable;
	std::list<std::string> m_upgradesHeroes;

	std::default_random_engine m_rng = std::default_random_engine{ (unsigned int)time(0) };
};