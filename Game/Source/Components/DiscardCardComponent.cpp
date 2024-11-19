#include "DiscardCardComponent.h"
#include "Engine.h"

void DiscardCardComponent::Initialize()
{
	ADD_OBSERVER(DiscardCard, DiscardCardComponent::OnOtherCardDiscard);
}

void DiscardCardComponent::Ability()
{
	EVENT_NOTIFY(TemporaryDiscardPhase);
	EVENT_NOTIFY_DATA(AddToDiscardQueue, new CardNameEventData(m_cardName, m_targetPlayer, m_deckID));
}

void DiscardCardComponent::OnOtherCardDiscard(const Event& event)
{
	if (auto data = dynamic_cast<CardNameEventData*>(event.data))
	{
		if (m_deckID == data->deckID)
		{
			int pointsAdded = m_defaultPointsAwarded;

			for (PointsAwardedPerCard card : m_specialPoints)
			{
				if (card.cardName == data->cardName)
				{
					pointsAdded = card.points;
					break;
				}
			}

			switch (m_trackerAddedTo)
			{
			case TrackerModifierCardComponent::Tracker::HEALTH:
			{
				EVENT_NOTIFY_DATA(ModifyHealth, new TrackerEventData(m_deckID, pointsAdded));
				break;
			}
			case TrackerModifierCardComponent::Tracker::GIMMICK:
			{
				EVENT_NOTIFY_DATA(ModifyGimmick, new TrackerEventData(m_deckID, pointsAdded));
				break;
			}
			case TrackerModifierCardComponent::Tracker::HERO_XP:
			{
				EVENT_NOTIFY_DATA(ModifyHeroXP, new TrackerEventData(m_deckID, pointsAdded));
				break;
			}
			default:
			{
				EVENT_NOTIFY_DATA(ModifyXP, new TrackerEventData(m_deckID, pointsAdded));
				break;
			}
			}
		}
		delete data;
	}
}


void DiscardCardComponent::Read(const json_t& value)
{
	std::vector<std::string> specialPointsList;

	READ_DATA_NAME(value, "minDiscard", m_minDiscard);
	READ_DATA_NAME(value, "maxDiscard", m_maxDiscard);
	READ_DATA_NAME(value, "defaultPointsAwarded", m_defaultPointsAwarded);
	READ_DATA_NAME(value, "specialPointsList", specialPointsList);

	for (std::string specialCase : specialPointsList)
	{
		std::string name;
		std::string points;

		std::stringstream stream(specialCase);
		std::getline(stream, name, ':');
		std::getline(stream, points, ':');

		int pointsParsed = std::stoi(points);

		m_specialPoints.push_back({ name, pointsParsed });
	}
}

void DiscardCardComponent::Write(json_t& value)
{
}

void DiscardCardComponent::Update(float dt)
{
}