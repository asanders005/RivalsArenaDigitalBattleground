#pragma once
#include "CardComponent.h"
#include "Event/EventManager.h"

class TrackerModifierCardComponent : public CardComponent
{
public:
	CLASS_DECLARATION(TrackerModifierCardComponent)
	CLASS_PROTOTYPE(TrackerModifierCardComponent)

	TrackerModifierCardComponent() = default;

	void Ability() override;

private:
	CardEnums::Tracker m_tracker = CardEnums::Tracker::HEALTH;
	int m_changeAmount = 0;

};