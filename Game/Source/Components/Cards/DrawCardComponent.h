#pragma once
#include "CardComponent.h"

class DrawCardComponent : public CardComponent
{
public:
	CLASS_DECLARATION(DrawCardComponent)
	CLASS_PROTOTYPE(DrawCardComponent)

	void Ability() override;
	void Initialize() override;

private:
	int m_pointCostPerCard = 0;
	int m_minCardsDrawn = 0;
	int m_maxCardsDrawn = 0;
	CardEnums::Tracker m_trackerSpent = CardEnums::Tracker::GIMMICK;

	int m_points;
	int m_cardsDrawing;

	void OnPlayConfirmation(const Event& event);
	void AbilityFunctionality();
};

