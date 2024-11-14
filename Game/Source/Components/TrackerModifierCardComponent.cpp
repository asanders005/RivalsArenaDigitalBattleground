#include "TrackerModifierCardComponent.h"

void TrackerModifierCardComponent::Play()
{
	CardComponent::Play();
	switch (m_tracker)
	{
	case Tracker::HEALTH:
	{
		EVENT_NOTIFY_DATA(ModifyHealth, TrackerEventData(m_targetPlayer, m_changeValue));
		break;
	}
	case Tracker::XP:
	{
		EVENT_NOTIFY_DATA(ModifyXP, TrackerEventData(m_targetPlayer, m_changeValue));
		break;
	}
	case Tracker::HERO_XP:
	{
		EVENT_NOTIFY_DATA(ModifyHeroXP, TrackerEventData(m_targetPlayer, m_changeValue));
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
