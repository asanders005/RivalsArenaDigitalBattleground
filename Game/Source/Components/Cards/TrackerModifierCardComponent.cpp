#include "TrackerModifierCardComponent.h"
#include "Framework/GameEventData.h"

FACTORY_REGISTER(TrackerModifierCardComponent);

void TrackerModifierCardComponent::Ability()
{
	switch (m_tracker)
	{
	case CardEnums::Tracker::HEALTH:
	{
		EVENT_NOTIFY_DATA(ModifyHealth, new TrackerEventData(m_targetPlayer, m_changeAmount));
		break;
	}
	case CardEnums::Tracker::XP:
	{
		EVENT_NOTIFY_DATA(ModifyXP, new TrackerEventData(m_targetPlayer, m_changeAmount));
		break;
	}
	case CardEnums::Tracker::HERO_XP:
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

	if (tracker == "XP") m_tracker = CardEnums::Tracker::XP;
	else if (tracker == "HERO_XP") m_tracker = CardEnums::Tracker::HERO_XP;
	else if (tracker == "GIMMICK") m_tracker = CardEnums::Tracker::GIMMICK;
	else m_tracker = CardEnums::Tracker::HEALTH;
}

void TrackerModifierCardComponent::Write(json_t& value)
{
}
