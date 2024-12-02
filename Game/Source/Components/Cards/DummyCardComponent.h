#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"

class DummyCardComponent : public Component, Observer
{
public:
	CLASS_DECLARATION(DummyCardComponent)
	CLASS_PROTOTYPE(DummyCardComponent)

	virtual ~DummyCardComponent();
		
	void Initialize() override;

	void Update(float dt) override;

	//Events
	void OnRefreshPileDisplay(const Event& event);
};