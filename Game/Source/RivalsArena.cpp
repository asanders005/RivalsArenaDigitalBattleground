#include "RivalsArena.h"
#include "Engine.h"

#include "Framework/GameEventData.h"
#include "Components/Players/DeckComponent.h"
#include "Components/Players/PlayerComponent.h"
#include "Components/Cards/CardComponent.h"
#include "Components/Cards/CounterComponent.h"
#include "Components/Cards/TrackerModifierCardComponent.h"

#include <functional>


bool RivalsArena::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);
	rapidjson::Document document;
	Json::Load("JSON/Initialize.json", document);
	m_scene->Read(document);
	Json::Load("JSON/Decks/FNAF/Cards.json", document);
	m_scene->Read(document);

	m_scene->Initialize();

	//m_audioController = m_scene->GetActor("audioController");

	/*m_pauseText = Factory::Instance().Create<Actor>("pauseText");
	m_pauseText->Initialize();*/

	//ADD_OBSERVER(CardPlayed, RivalsArena::OnCardPlay);
	ADD_OBSERVER(CheckCard, RivalsArena::OnCheckCard);

	return true;
}

void RivalsArena::Shutdown()
{
	m_scene->RemoveAll(true);
}

void RivalsArena::Update(float dt)
{
	switch (m_state)
	{
	case RivalsArena::eState::TITLE:
		break;
	case RivalsArena::eState::GAME_START:
		CreatePlayer("test");
		m_players.push_back("test");
		m_activePlayer = m_players[random(m_players.size())];

		for (auto& player : m_players)
		{
			EVENT_NOTIFY_DATA(DrawCard, new StringEventData{ player });
		}
		m_state = RivalsArena::eState::UPKEEP;
		break;
	case RivalsArena::eState::UPKEEP:
		break;
	case RivalsArena::eState::MAIN:
		break;
	case RivalsArena::eState::BUY:
		break;
	case RivalsArena::eState::END:
		break;
	case RivalsArena::eState::REACT:
		break;
	case RivalsArena::eState::SELECTION:
		break;
	case RivalsArena::eState::GAME_OVER:
		break;
	}
	m_scene->Update(dt);
}

void RivalsArena::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void RivalsArena::OnCheckCard(const Event& event)
{

}

void RivalsArena::CreatePlayer(const std::string& playerID)
{
	if (auto player = Factory::Instance().Create<Actor>("player"))
	{
		player->GetComponent<PlayerComponent>()->playerID = playerID;

		std::unique_ptr<Component> deck = std::make_unique<DeckComponent>(playerID);
		rapidjson::Document document;
		Json::Load("JSON/Decks/FNAF/Deck.json", document);
		deck->Read(document);
		player->AddComponent(std::move(deck));

		m_scene->AddActor(std::move(player), true);
	}
}
