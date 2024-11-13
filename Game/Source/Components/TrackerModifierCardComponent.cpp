#include "TrackerModifierCardComponent.h"

void TrackerModifierCardComponent::Play()
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

void TrackerModifierCardComponent::Read(const json_t& value)
{
}

void TrackerModifierCardComponent::Write(json_t& value)
{
}

void TrackerModifierCardComponent::Initialize()
{
}

void TrackerModifierCardComponent::Update(float dt)
{
}
