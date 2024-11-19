#pragma once
#include "Components/Component.h"
#include "Event/EventManager.h"

class PileComponent : public Component, Observer
{
public:
	CLASS_DECLARATION(PileComponent)
	CLASS_PROTOTYPE(PileComponent)

	void Initialize() override;

	void Update(float dt) override;

	void SetData(const std::string& playerID, const std::string& pileName)
	{
		m_playerID = playerID;
		m_name = pileName;
	}

	void UpdateTexture(const std::string& textureName);
	void OnUpdateTexture(const Event& event);

private:
	std::string m_playerID;
	std::string m_name;
};