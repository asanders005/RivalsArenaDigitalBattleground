#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"

class PlayerComponent : public Component, Observer
{
public:
	CLASS_DECLARATION(PlayerComponent)
	CLASS_PROTOTYPE(PlayerComponent)

	void Initialize() override;

	void Update(float dt) override;

	void OnUpdateTracker(const Event& event);

private:
	int m_health = 0;
	int m_exp = 0;
	int m_heroExp = 0;

	int in_hand = 5;

	std::string id;
	bool isActive = false;

	// Events
	void ModifyPlayerHealth(const Event& event);
	void ChangeExp(const Event& event);
	void ChangeHeroExp(const Event& event);
	void OnReact(const Event& event);
};