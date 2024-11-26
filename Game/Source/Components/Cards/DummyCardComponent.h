#pragma once
#include "Components/Cards/CardComponent.h"
#include "Event/EventManager.h"

class DummyCardComponent : public Component, Observer
{
	CLASS_DECLARATION(DummyCardComponent)
	CLASS_PROTOTYPE(DummyCardComponent)

	void Initialize() override;

	void Update(float dt) override;

	//Events
	void OnRefreshPileDisplay(const Event& event);

private:
	std::string m_cardName;
	CardEnums::CardTier m_tier;

	bool isDestroyed = false;
};