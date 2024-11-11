#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"

class DeckComponent : public Component, public Observer
{
public:
	CLASS_DECLARATION(DeckComponent)
	CLASS_PROTOTYPE(DeckComponent)

	void Initialize() override;

	void Update(float dt) override;

	void OnDraw(const Event& event);
	void OnDiscard(const Event& event);
	void OnBuyHero(const Event& event);
	void OnBuyConsumable(const Event& event);
	void OnUpgradeConsumable(const Event& event);

private:
	// Deck will read deck file in Initialize
	std::vector<std::string> m_draw;
	std::vector<std::string> m_discard;
	std::vector<std::string> m_upgradesConsumable;
	std::vector<std::string> m_upgradesHeroes;
};