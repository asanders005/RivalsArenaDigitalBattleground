#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"

class ButtonComponent : public Component, Observer
{
	CLASS_DECLARATION(ButtonComponent)
	CLASS_PROTOTYPE(ButtonComponent)

	void Initialize() override;

	void Update(float dt) override;

	void OnUpdateText(const Event& event);

public:
	std::string buttonID;
};