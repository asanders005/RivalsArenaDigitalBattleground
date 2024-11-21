#pragma once
#include "Components/Component.h"

class CounterComponent : public Component
{
public:
	enum class eCounterType
	{
		DAMAGE,
		DAMAGE_INSTANCE,
		SHIELD,
		HERO
	};
public:
	// implement defaults
		// add observers based on the counter type

private:
	int m_targetCount = 0;
	int m_currentCount = 0;
};