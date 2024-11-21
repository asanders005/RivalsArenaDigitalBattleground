#pragma once
#include "CardComponent.h"
#include "Event/EventManager.h"

class IncomingDamageCardComponent : public CardComponent
{
public:
	CLASS_DECLARATION(IncomingDamageCardComponent)
	CLASS_PROTOTYPE(IncomingDamageCardComponent)

	void Ability() override;
	void Initialize() override;
	void Update(float dt) override;

private:
	int m_baseModificationAmount = 0;
	bool m_multiply = false;
	bool m_roundUp = false;
	int m_maxPointsSpent = 0;
	int m_minPointsSpent = 0;
	float m_modificationPerPointSpent = 0;
	CardEnums::Tracker m_trackerSpent = CardEnums::Tracker::GIMMICK;

	int m_points;
	float m_modification;

	void OnPlayConfirmation(const Event& event);
	void AbilityFunctionality();
};

