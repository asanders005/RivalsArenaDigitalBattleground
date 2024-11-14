#pragma once
#include "Components/Component.h"

class CardComponent : public Component
{
	CLASS_DECLARATION(CardComponent)
	CLASS_PROTOTYPE(CardComponent)

	void Initialize() override;

	void Update(float dt) override;

};