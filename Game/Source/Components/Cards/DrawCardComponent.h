#pragma once
#include "CardComponent.h"

class DrawCardComponent : public CardComponent
{
public:
	CLASS_DECLARATION(DrawCardComponent)
	CLASS_PROTOTYPE(DrawCardComponent)

	void Ability() override;
	void Initialize() override;
	void Update(float dt) override;

private:
	int m_pointCostPerCard = 0;
	int m_minCardsDrawn = 0;
	int m_maxCardsDrawn = 0;
	Tracker m_trackerSpent = Tracker::GIMMICK;

	int m_points;
	int m_cardsDrawing;

	void OnPlayConfirmation(const Event& event);
	void AbilityFunctionality();
};

