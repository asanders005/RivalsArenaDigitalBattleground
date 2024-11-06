#include "Engine.h"

#include <iostream>

int main(int argc, char* argv[])
{
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	while (!engine->IsQuit())
	{
		// update
		engine->Update();

		// render
		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		engine->GetPS().Draw(engine->GetRenderer());

		engine->GetRenderer().EndFrame();
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}