#include "Engine.h"
#include "RivalsArena.h"

#include "Components/DeckComponent.h"
#include "Framework/GameEventData.h"

#include <iostream>

int main(int argc, char* argv[])
{
	srand((int)time(0));

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	auto engine = std::make_unique<Engine>();
	engine->Initialize();

	auto game = std::make_unique<RivalsArena>(engine.get());
	game->Initialize();

	DeckComponent deck;
	deck.Initialize();
	for (int i = 0; i < 5; i++)
	{
		EVENT_NOTIFY_DATA(DrawCard, TargetEventData("5"));
	}

	EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData("card", "5"));
	EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData("card", "5"));
	EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData("card", "5"));
	EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData("card1", "5"));
	EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData("card1", "5"));
	EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData("card1", "5"));
	EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData("card2", "5"));
	EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData("card2", "5"));
	EVENT_NOTIFY_DATA(DiscardCard, CardNameEventData("card3", "5"));

	while (!engine->IsQuit())
	{
		// update
		engine->Update();
		game->Update(engine->GetTime().GetDeltaTime());

		// render
		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		game->Draw(engine->GetRenderer());

		engine->GetPS().Draw(engine->GetRenderer());

		engine->GetRenderer().EndFrame();
	}

	game->Shutdown();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}