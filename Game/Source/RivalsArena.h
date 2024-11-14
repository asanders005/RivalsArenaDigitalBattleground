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
		END,
		REACT,
		GAME_OVER
	};

public:
	RivalsArena(Engine* engine) : Game{ engine } {}

	bool Initialize() override;

	void Shutdown() override;

	void Update(float dt) override;

	void Draw(Renderer& renderer) override;

	// Events
	// -----------Template---------------
	// void OnLevelComplete(const Event& event);
	void OnCardPlay(const Event& event);

private:
	eState m_state{ eState::TITLE };
	std::vector<std::string> m_players;

	std::unique_ptr<class Scene> m_scene;
	class Actor* m_audioController{ nullptr };
};