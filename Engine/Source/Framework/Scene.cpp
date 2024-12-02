#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Core/EAssert.h"
#include "Core/EString.h"
#include "Components/CollisionComponent.h"

Scene::Scene(const Scene& other)
{
	ASSERT(false);
}

void Scene::Initialize()
{
	for (auto& actor : actors)
	{
		actor->Initialize();
	}
}

void Scene::Update(float dt)
{
	auto iter = actors.begin();
	while (iter != actors.end())
	{
		if ((*iter)->isActive && !(*iter)->isDestroyed)
		{
			(*iter)->Update(dt);
			++iter; // only increment when not erasing
		}
		else
		{
			iter = actors.erase(iter); // erase and update iterator
		}
	}


	//for (auto& actor : actors)
	//{
	//	if (actor->isActive && !actor->isDestroyed) actor->Update(dt);
	//	if (actor->isDestroyed)
	//	{

	//		//std::cout << "destroyed: " << actor->name << std::endl;
	//	}
	//}
	//

	//std::erase_if(actors, [](auto& actor) { return actor->isDestroyed; });
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : actors)
	{		
		if (actor->isActive) actor->Draw(renderer);
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor, bool initialize)
{
	actor->scene = this;
	static int id = 0;
	actor->name = "created: " + actor->name + std::to_string(id++);
	if (initialize) actor->Initialize();
	actors.push_back(std::move(actor));
}

Actor* Scene::GetActor(const std::string& name)
{
	for (auto& actor : actors)
	{
		auto result = actor.get();
		if (result && IsEqualIgnoreCase(result->name, name)) return result;
	}

	return nullptr;
}

std::vector<Actor*> Scene::GetActors(const std::string& name)
{
	std::vector<Actor*> result;
	for (auto& actor : actors)
	{
		auto a = actor.get();
		if (a && IsEqualIgnoreCase(a->name, name)) result.push_back(a);
	}

	return result;
}

void Scene::RemoveAll(bool force)
{
	std::erase_if(actors, [force](auto& actor) { return (force || !actor->isPersistent); });
}

void Scene::RemoveAll(std::string tag)
{
	std::erase_if(actors, [tag](auto& actor) { return actor->tag == tag; });
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			bool prototype = false;
			READ_DATA(actorValue, prototype);

			if (prototype)
			{
				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
			else
			{ 
				AddActor(std::move(actor));
			}
		}
	}
}

void Scene::Write(json_t& value)
{
	//
}
