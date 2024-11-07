#pragma once
#include "Components/Component.h"

class CardComponent : public Component
{
	std::unique_ptr<Object> Clone() override;
	void Initialize() override;
	void Update(float dt) override;
};