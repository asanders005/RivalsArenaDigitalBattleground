#pragma once
#include "CardComponent.h"
#include "Event/EventManager.h"


class DiscardCardComponent : public CardComponent
{
public:
	CLASS_DECLARATION(DiscardCardComponent)
	CLASS_PROTOTYPE(DiscardCardComponent)

	void Ability() override;
	void Initialize() override;

	struct PointsAwardedPerCard {
		std::string cardName;
		int points;
	};


private:
	int m_minDiscard = 0;
	int m_maxDiscard = 0;
	int m_defaultPointsAwarded = 0;
	std::vector<PointsAwardedPerCard> m_specialPoints;
	CardEnums::Tracker m_trackerAddedTo = CardEnums::Tracker::XP;

	void OnOtherCardDiscard(const Event& event);

};

