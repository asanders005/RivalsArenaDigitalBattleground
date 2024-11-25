#pragma once
#include "Framework/Game.h"
#include "Event/EventManager.h"
#include <memory>

class RivalsArena : public Game, Observer
{
public:
	enum class eState
	{
		TITLE,
		GAME_START,
		UPKEEP,
		MAIN,
		BUY,
		DISCARD,
		END,
		SELECTION,
		REACT,
		GAME_OVER
	};

public:
	RivalsArena(Engine* engine) : Game{ engine } {}

	bool Initialize() override;

	void Shutdown() override;

	void Update(float dt) override;

	void Draw(Renderer& renderer) override;

	//Events
	void OnCheckCard(const Event& event);
	void OnSelectPlayer(const Event& event);
	void OnButtonPressed(const Event& event);

private:
	void CreatePlayer(const std::string& playerID, bool isCPU = false);
	void CreateButton(const std::string& buttonID, struct Vector2 position, bool isVisible);

private:
	eState m_state{ eState::GAME_START };
	eState m_prevState;

	std::vector<std::string> m_players;
	std::string m_activePlayer;
	int m_activePlayerIndex;

	std::vector<std::string> m_selectButtonIDs;
	std::string pendingCardID;

	std::unique_ptr<class Scene> m_scene;
	class Actor* m_audioController{ nullptr };
};