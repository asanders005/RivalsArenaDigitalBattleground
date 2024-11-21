#include "IncomingDamageCardComponent.h"
#include "Framework/GameEventData.h"

FACTORY_REGISTER(IncomingDamageCardComponent);

void IncomingDamageCardComponent::Initialize()
{
	ADD_OBSERVER(PlayConfirmation, IncomingDamageCardComponent::OnPlayConfirmation);
}

void IncomingDamageCardComponent::Ability()
{
	m_points = 0;
	m_modification = m_baseModificationAmount;
	if (m_maxPointsSpent == m_minPointsSpent) m_points = m_maxPointsSpent;
	else
	{
		// Prompt the player for amount of points to spend
		m_modification += (m_points * m_modificationPerPointSpent);
	}

	if (m_modification == 0) return;

	if (m_points == 0) AbilityFunctionality();
	else EVENT_NOTIFY_DATA(TrySpendPoints, new PointSpendingQueryEventData(m_deckID, m_cardID, -m_points, m_trackerSpent));
}

void IncomingDamageCardComponent::OnPlayConfirmation(const Event& event)
{
	if (auto data = dynamic_cast<CardIDEventData*>(event.data))
	{
		if (m_cardID == data->cardID)
		{
			AbilityFunctionality();
		}
	}
}

void IncomingDamageCardComponent::AbilityFunctionality()
{
	if (m_multiply) EVENT_NOTIFY_DATA(MultiplyIncomingDamage, new TrackerEventData(m_deckID, m_modification, m_roundUp));
	else EVENT_NOTIFY_DATA(AddIncomingDamage, new TrackerEventData(m_deckID, m_modification));

	switch (m_trackerSpent)
	{
	case CardEnums::Tracker::HEALTH:
	{
		EVENT_NOTIFY_DATA(ModifyHealth, new TrackerEventData(m_deckID, -m_points));
		break;
	}
	case CardEnums::Tracker::XP:
	{
		EVENT_NOTIFY_DATA(ModifyXP, new TrackerEventData(m_deckID, -m_points));
		break;
	}
	case CardEnums::Tracker::HERO_XP:
	{
		EVENT_NOTIFY_DATA(ModifyHeroXP, new TrackerEventData(m_deckID, -m_points));
		break;
	}
	default:
	{
		EVENT_NOTIFY_DATA(ModifyGimmick, new TrackerEventData(m_deckID, -m_points));
		break;
	}
	}

	DiscardCard();
}

void IncomingDamageCardComponent::Update(float dt)
{
}

void IncomingDamageCardComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "BaseModificationAmount", m_baseModificationAmount);
	READ_DATA_NAME(value, "Multiply", m_multiply);
	READ_DATA_NAME(value, "RoundUp", m_roundUp);
	READ_DATA_NAME(value, "MaxPointsSpent", m_maxPointsSpent);
	READ_DATA_NAME(value, "MinPointsSpent", m_minPointsSpent);
	READ_DATA_NAME(value, "ModificationPerPoint", m_modificationPerPointSpent);

	std::string tracker = "";
	READ_DATA_NAME(value, "Tracker", tracker);

	if (tracker == "XP") m_trackerSpent = CardEnums::Tracker::XP;
	else if (tracker == "HERO_XP") m_trackerSpent = CardEnums::Tracker::HERO_XP;
	else if (tracker == "HEALTH") m_trackerSpent = CardEnums::Tracker::HEALTH;
	else m_trackerSpent = CardEnums::Tracker::GIMMICK;
}

void IncomingDamageCardComponent::Write(json_t& value)
{
}