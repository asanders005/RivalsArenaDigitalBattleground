#pragma once
#include <list>
#include "rapidjson/document.h"

#include "Components/Component.h"

class DeckComponent : public Component
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

	void Initialize() override;

	void Update(float dt) override;


private:
	// Deck will read deck file in Initialize
	std::string m_deckFile;
	std::list<std::string> m_draw;
	std::list<std::string> m_upgradesConsumable;
	std::list<std::string> m_upgradesHeroes;
	//std::map<std::string, std::unique_ptr<class Card>> m_cards;
};