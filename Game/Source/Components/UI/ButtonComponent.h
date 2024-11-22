#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"

class ButtonComponent : public Component, Observer
{
public:
	CLASS_DECLARATION(ButtonComponent)
	CLASS_PROTOTYPE(ButtonComponent)

	void Initialize() override;

	void Update(float dt) override;

public:
	std::string buttonID;
};