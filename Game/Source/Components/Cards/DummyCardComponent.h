#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"

class DummyCardComponent : public Component, Observer
{
	CLASS_DECLARATION(DummyCardComponent)
	CLASS_PROTOTYPE(DummyCardComponent)

	void Initialize() override;

	void Update(float dt) override;

	//Events
	void OnRefreshPileDisplay(const Event& event);
};