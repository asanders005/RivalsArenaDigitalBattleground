#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"

class PileComponent : public Component, Observer
{
	CLASS_DECLARATION(PileComponent)
	CLASS_PROTOTYPE(PileComponent)

	void Initialize() override;

	void Update(float dt) override;

	void OnUpdateTexture(const Event& event);

private:
	std::string m_name;
};