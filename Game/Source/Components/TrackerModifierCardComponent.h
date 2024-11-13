#pragma once
#include "CardComponent.h"
#include "../Framework/GameEventData.h"
#include "Event/EventManager.h"


class TrackerModifierCardComponent : public CardComponent
{
public:
	CLASS_DECLARATION(TrackerModifierCardComponent)
	CLASS_PROTOTYPE(TrackerModifierCardComponent)

	enum class TrackerType
	{
		HEALTH,
		XP,
		GIMMICK
	};

	void Play() override;

private:
	TrackerType m_tracker = TrackerType::HEALTH;
	int m_changeValue = 0;


	// Inherited via CardComponent
	void Initialize() override;

	void Update(float dt) override;

};