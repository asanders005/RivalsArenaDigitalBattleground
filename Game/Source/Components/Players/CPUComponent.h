#pragma once
#include "PlayerComponent.h"
#include "Event/EventManager.h"
#include "RivalsArena.h"


class CPUComponent : public PlayerComponent
{
public:
    CLASS_DECLARATION(CPUComponent)
	CLASS_PROTOTYPE(CPUComponent)


    void Initialize() override;

    void Update(float dt) override;

    //Getters
    int GetHealth() { return m_health; }
    int GetExp() { return m_exp; }
    int GetHeroExp() { return m_heroExp; }
    std::string GetID() { return playerID; }
    bool GetIsActive() { return isActive; }
    bool GetIsDied() { return isDied; }

    //Setters
    void SetCPUID(std::string cpuName) { playerID = cpuName; }


    void ExecuteTurn();
    void DrawCard();
    void DiscardCard(const std::string& cardName);
    void EvaluateCards();
    void SortHandByPriority();
    void PlayBestCard();
    void SetGameState(RivalsArena::eState& state) { gameState = state; }
    int EvaluateCardPriority(const std::string& cardName);

    //Events
    void EndTurn(const Event& event);
    void React(const Event& event) override;
    const std::list<std::string>& GetHand() const;
    class CardComponent* GetCardComponent(const std::string& cardName);

public:
    std::string playerID;

private:

    int m_health = 0;
    int m_exp = 0;
    int m_heroExp = 0;
    bool isActive = false;
    bool isDied = false;

    RivalsArena::eState gameState;
    class DeckComponent* m_deck;
    std::list<std::string> m_hand;
};
