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

	void Play() override
	{
		CardComponent::Play();
		switch (m_tracker)
		{
			case TrackerType::HEALTH:
			{
				EVENT_NOTIFY_DATA(ModifyHealth, TrackerEventData(m_targetPlayer, m_changeValue));
				break;
			}
			case TrackerType::XP:
			{
				EVENT_NOTIFY_DATA(ModifyXP, TrackerEventData(m_targetPlayer, m_changeValue));
				break;
			}
			default:
			{
				EVENT_NOTIFY_DATA(ModifyGimmick, TrackerEventData(m_targetPlayer, m_changeValue));
				break;
			}
		}
	}

private:
	TrackerType m_tracker = TrackerType::HEALTH;
	int m_changeValue = 0;


	// Inherited via CardComponent
	void Initialize() override;

	void Update(float dt) override;

};