#pragma once
#include "Components/Component.h"

class DeckComponent : public Component
{
public:
	CLASS_DECLARATION(DeckComponent)
	CLASS_PROTOTYPE(DeckComponent)

	void Initialize() override;

	void Update(float dt) override;


private:
	// Deck will read deck file in Initialize
	std::string m_deckFile;
	//std::map<std::string, std::unique_ptr<class Card>> m_cards;
};