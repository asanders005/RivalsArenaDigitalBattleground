#include "RivalsArena.h"
#include "Engine.h"

#include <functional>


bool RivalsArena::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);
	/*rapidjson::Document document;
	Json::Load("Scenes/Initialize.json", document);
	m_scene->Read(document);
	Json::Load("Scenes/Title.json", document);
	m_scene->Read(document);*/

	m_scene->Initialize();

	m_audioController = m_scene->GetActor("audioController");

	/*m_pauseText = Factory::Instance().Create<Actor>("pauseText");
	m_pauseText->Initialize();*/

	/*ADD_OBSERVER(PlayerDead, FungalLeap::OnPlayerDead);
	ADD_OBSERVER(AddPoints, FungalLeap::OnAddPoints);
	ADD_OBSERVER(LevelComplete, FungalLeap::OnLevelComplete);*/

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
	}
}

void RivalsArena::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}
