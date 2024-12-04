#pragma once
#include "Object.h"
#include <list>
#include <string>
#include <vector>
#include <memory>

class Renderer;
class Actor;
class Game;
class Engine;

class Scene : public Object
{
public:
	Scene(Engine* engine, Game* game = nullptr) : engine{ engine }, game { game } {}
	Scene(const Scene& other);

	void Initialize() override;

	CLASS_DECLARATION(Scene)
	CLASS_PROTOTYPE(Scene)

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor, bool initialize = false);
	

	void RemoveAll(bool force = false);
	void RemoveAll(std::string tag);

	Actor* GetActor(const std::string& name);
	std::vector<Actor*> GetActors(const std::string& name);

public:
	Engine* engine{ nullptr };
	Game* game{ nullptr };
	
	std::list<std::unique_ptr<Actor>> actors;
private:
};
