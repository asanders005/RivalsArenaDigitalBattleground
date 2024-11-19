#pragma once
#include "CardComponent.h"
#include "../Framework/GameEventData.h"
#include "Event/EventManager.h"
#include "TrackerModifierCardComponent.h"


class DiscardCardComponent : public CardComponent
{
public:
	CLASS_DECLARATION(DiscardCardComponent)
	CLASS_PROTOTYPE(DiscardCardComponent)

	void Ability() override;
	void Initialize() override;
	void Update(float dt) override;

	struct PointsAwardedPerCard {
		std::string cardName;
		int points;
	};


private:
	int m_minDiscard = 0;
	int m_maxDiscard = 0;
	int m_defaultPointsAwarded = 0;
	std::vector<PointsAwardedPerCard> specialPoints;

	void OnOtherCardDiscard(const Event& event);

	// Inherited via CardComponent

};

