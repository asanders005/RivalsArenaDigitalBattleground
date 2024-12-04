#include "RivalsArena.h"
#include "Engine.h"

#include "Framework/GameEventData.h"
#include "Components/Players/DeckComponent.h"
#include "Components/Players/PlayerComponent.h"
#include "Components/Players/CPUComponent.h"
#include "Components/Cards/CardComponent.h"
#include "Components/Cards/CounterComponent.h"
#include "Components/Cards/TrackerModifierCardComponent.h"
#include "Components/UI/ButtonComponent.h"

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
	ADD_OBSERVER(TryPlayCard, RivalsArena::OnCheckCard);
	ADD_OBSERVER(SelectPlayer, RivalsArena::OnSelectPlayer);
	ADD_OBSERVER(ButtonClicked, RivalsArena::OnButtonPressed);

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
		CreatePlayer("player");
		m_players.push_back("player");
		CreatePlayer("CPU", true);
		m_players.push_back("CPU");
		
		m_activePlayerIndex = random(m_players.size());
		m_activePlayer = m_players[m_activePlayerIndex];

		for (auto& player : m_players)
		{
			EVENT_NOTIFY_DATA(DrawCard, new StringEventData{ player });
			CreateButton("PlayerSelect_" + player, Vector2{ randomf(200.0f, 800.0f), 300.0f }, false);
			m_selectButtonIDs.push_back("PlayerSelect_" + player);

			//CreateButton("PlayerHealth: " + m_scene->GetActor(player)->GetComponent<CPUComponent>()->GetHealth(), true)
		}

		CreateButton("BtnNextPhase", { 800, 500 }, true);
		m_state = RivalsArena::eState::UPKEEP;
		break;
	case RivalsArena::eState::UPKEEP:
		std::cout << m_activePlayer << "'s Turn" << std::endl;

		EVENT_NOTIFY_DATA(Upkeep, new PlayerStringEventData(m_activePlayer, "CPUTurn"));

		m_state = RivalsArena::eState::MAIN;
		break;
	case RivalsArena::eState::MAIN:
		EVENT_NOTIFY_DATA(SelectPlayer, new CardIDEventData("Player1_Test"));

		if (m_activePlayer == "CPU")
		{
			m_state == eState::END;
		}
		break;
	case RivalsArena::eState::BUY:
		break;
	case RivalsArena::eState::DISCARD:
		break;
	case RivalsArena::eState::END:
		EVENT_NOTIFY_DATA(DrawCard, new StringEventData(m_activePlayer));

		m_activePlayerIndex = (m_activePlayerIndex + 1 >= m_players.size()) ? 0 : m_activePlayerIndex + 1;
		m_activePlayer = m_players[m_activePlayerIndex];
		m_state = RivalsArena::eState::UPKEEP;
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
	if (auto data = dynamic_cast<CardPhaseInfoEventData*>(event.data))
	{
		std::cout << "Check Card: " << data->cardId << "; Phase: " << (int)data->phase << std::endl;
		switch (m_state)
		{
		case RivalsArena::eState::UPKEEP:
			if (data->phase == CardEnums::PlayPhase::START_OF_TURN) EVENT_NOTIFY_DATA(PlayCard, new CardIDEventData(data->cardId));
			break;
		case RivalsArena::eState::MAIN:
			if (data->phase == CardEnums::PlayPhase::TURN)
			{
				EVENT_NOTIFY_DATA(PlayCard, new CardIDEventData(data->cardId));
			}
			break;
		case RivalsArena::eState::END:
			if (data->phase == CardEnums::PlayPhase::END_OF_TURN) EVENT_NOTIFY_DATA(PlayCard, new CardIDEventData(data->cardId));
			break;
		case RivalsArena::eState::REACT:
			if (data->phase == CardEnums::PlayPhase::REACTION) EVENT_NOTIFY_DATA(PlayCard, new CardIDEventData(data->cardId));
			break;
		}
	}
}

void RivalsArena::OnSelectPlayer(const Event& event)
{
	if (auto data = dynamic_cast<CardIDEventData*>(event.data))
	{
		if (data->cardID.substr(0, 3) != "CPU" && pendingCardID != "")
		{
			pendingCardID = data->cardID;
			for (auto button : m_selectButtonIDs)
			{
				EVENT_NOTIFY_DATA(DisplayButton, new StringBoolEventData(button, true));
			}
		}
	}
}

void RivalsArena::OnButtonPressed(const Event& event)
{
	if (auto data = dynamic_cast<StringEventData*>(event.data))
	{
		if (data->string == "BtnNextPhase")
		{
			switch (m_state)
			{
			case RivalsArena::eState::MAIN:
				m_state = RivalsArena::eState::BUY;
				break;
			case RivalsArena::eState::BUY:
				m_state = RivalsArena::eState::END;
				break;
			case RivalsArena::eState::REACT:
				m_state = m_prevState;
				break;
			}
			std::cout << "Phase: " << (int)m_state << std::endl;
		}
		else if (data->string.substr(0, 12) == "PlayerSelect")
		{
			std::cout << "Selected Player: " << data->string.substr(13) << std::endl;
			EVENT_NOTIFY_DATA(PlayerSelected, new PlayerStringEventData(data->string.substr(13), pendingCardID));
			for (auto button : m_selectButtonIDs)
			{
				EVENT_NOTIFY_DATA(DisplayButton, new StringBoolEventData(button, false));
			}
			pendingCardID = "";
		}
	}
}

void RivalsArena::CreatePlayer(const std::string& playerID, bool isCPU)
{
	if (isCPU)
	{
		if (auto player = Factory::Instance().Create<Actor>("CPUPlayer"))
		{
			

			player->GetComponent<CPUComponent>()->playerID = playerID;
			player->GetComponent<CPUComponent>()->SetCPUID(playerID);
			player->GetComponent<CPUComponent>()->SetID(playerID);

			std::unique_ptr<Component> deck = std::make_unique<DeckComponent>(playerID);
			rapidjson::Document document;
			Json::Load("JSON/Decks/FNAF/Deck.json", document);
			deck->Read(document);
			player->AddComponent(std::move(deck));

			player->GetComponent<CPUComponent>()->SetDeckComponent(player->GetComponent<DeckComponent>());
			player->GetComponent<CPUComponent>()->my_hand = player->GetComponent<DeckComponent>()->GetHand();

			m_scene->AddActor(std::move(player), true);
		}
	}
	else if (auto player = Factory::Instance().Create<Actor>("player"))
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

void RivalsArena::CreateButton(const std::string& buttonID, Vector2 position, bool isVisible)
{
	if (auto button = Factory::Instance().Create<Actor>("UniversalButton"))
	{
		button->GetComponent<ButtonComponent>()->buttonID = buttonID;
		button->transform.position = position;

		m_scene->AddActor(std::move(button), true);
	}
}