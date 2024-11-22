#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"

class PlayerComponent : public Component, Observer
{
public:
	CLASS_DECLARATION(PlayerComponent)
	CLASS_PROTOTYPE(PlayerComponent)

	void Initialize() override;

	void Update(float dt) override;

	void OnUpdateTracker(const Event& event);

	// Events
	void ModifyPlayerHealth(const Event& event);
	void ChangeExp(const Event& event);
	void ChangeHeroExp(const Event& event);
	virtual void React(const Event& event);

public:

	int GetHealth() { return m_health; }
	int GetExp() { return m_exp; }
	int GetHeroExp() { return m_heroExp; }
	std::string GetID() { return playerID; }
	bool GetIsActive() { return isActive; }
	bool GetIsDied() { return isDied; }
	void SetID(std::string playername) { playerID = playername; }

	std::string playerID = "player";

private:

	int m_health = 0;
	int m_exp = 0;
	int m_heroExp = 0;
	bool isActive = false;
	bool isDied = false;


};
