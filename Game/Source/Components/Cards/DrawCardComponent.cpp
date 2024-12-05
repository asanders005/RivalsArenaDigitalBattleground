#include "DrawCardComponent.h"
#include "Framework/GameEventData.h"

void DrawCardComponent::Initialize()
{
	CardComponent::Initialize();

	ADD_OBSERVER(PlayConfirmation, DrawCardComponent::OnPlayConfirmation);
}

void DrawCardComponent::Ability()
{
	m_points = 0;
	m_cardsDrawing = 0;
	if (m_minCardsDrawn == m_maxCardsDrawn) m_cardsDrawing = m_maxCardsDrawn;
	else
	{
		//TODO: Prompt the player for amount of cards to draw
	}
	m_points = m_cardsDrawing * m_pointCostPerCard;

	if (m_cardsDrawing == 0) return;

	if (m_points == 0) AbilityFunctionality();
	else EVENT_NOTIFY_DATA(TrySpendPoints, new PointSpendingQueryEventData(m_deckID, m_cardID, -m_points, m_trackerSpent));
}

void DrawCardComponent::OnPlayConfirmation(const Event& event)
{
	if (auto data = dynamic_cast<CardIDEventData*>(event.data))
	{
		if (m_cardID == data->cardID)
		{
			AbilityFunctionality();
		}
	}
}

void DrawCardComponent::AbilityFunctionality()
{
	for (int i = 0; i < m_cardsDrawing; i++)
	{
		EVENT_NOTIFY_DATA(DrawCards, new StringEventData(m_deckID));
	}

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

void DrawCardComponent::Read(const json_t& value)
{
	READ_DATA_NAME(value, "pointCostPerCard", m_pointCostPerCard);
	READ_DATA_NAME(value, "minCardsDrawn", m_minCardsDrawn);
	READ_DATA_NAME(value, "maxCardsDrawn", m_maxCardsDrawn);

	std::string tracker = "";
	READ_DATA_NAME(value, "tracker", tracker);

	if (tracker == "XP") m_trackerSpent = CardEnums::Tracker::XP;
	else if (tracker == "HERO_XP") m_trackerSpent = CardEnums::Tracker::HERO_XP;
	else if (tracker == "HEALTH") m_trackerSpent = CardEnums::Tracker::HEALTH;
	else m_trackerSpent = CardEnums::Tracker::GIMMICK;
}

void DrawCardComponent::Write(json_t& value)
{
}
