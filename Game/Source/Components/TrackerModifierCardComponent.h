#pragma once
#include "CardComponent.h"


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