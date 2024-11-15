#pragma once
#include "CardComponent.h"
#include "../Framework/GameEventData.h"
#include "Event/EventManager.h"


class TrackerModifierCardComponent : public CardComponent
{
public:
	CLASS_DECLARATION(TrackerModifierCardComponent)
	CLASS_PROTOTYPE(TrackerModifierCardComponent)

	enum class Tracker
	{
		HEALTH,
		XP,
		HERO_XP,
		GIMMICK
	};

	void Play() override;

private:
	Tracker m_tracker = Tracker::HEALTH;
	int m_changeAmount = 0;


	// Inherited via CardComponent
	void Initialize() override;

	void Update(float dt) override;

};