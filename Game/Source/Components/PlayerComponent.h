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

};