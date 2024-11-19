#include "TrackerModifierCardComponent.h"

void TrackerModifierCardComponent::Ability()
{
	switch (m_tracker)
	{
	case Tracker::HEALTH:
	{
		EVENT_NOTIFY_DATA(ModifyHealth, new TrackerEventData(m_targetPlayer, m_changeAmount));
		break;
	}
	case Tracker::XP:
	{
		EVENT_NOTIFY_DATA(ModifyXP, new TrackerEventData(m_targetPlayer, m_changeAmount));
		break;
	}
	case Tracker::HERO_XP:
	{
		EVENT_NOTIFY_DATA(ModifyHeroXP, new TrackerEventData(m_targetPlayer, m_changeAmount));
		break;
	}
	default:
	{
		EVENT_NOTIFY_DATA(ModifyGimmick, new TrackerEventData(m_targetPlayer, m_changeAmount));
		break;
	}
	}

	DiscardCard();
}

void TrackerModifierCardComponent::Read(const json_t& value)
{
	CardComponent::Read(value);

	READ_DATA_NAME(value, "ChangeAmount", m_changeAmount);

	std::string tracker = "";
	READ_DATA_NAME(value, "Tracker", tracker);

	if (tracker == "XP") m_tracker = Tracker::XP;
	else if (tracker == "HERO_XP") m_tracker = Tracker::HERO_XP;
	else if (tracker == "GIMMICK") m_tracker = Tracker::GIMMICK;
	else m_tracker = Tracker::HEALTH;
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
