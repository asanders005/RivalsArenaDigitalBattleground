
#pragma once
#include <vector>
#include <string>
#include "..//Cards/CardComponent.h"
#include "RivalsArena.h"
#include "PlayerComponent.h"


class CPUComponent : PlayerComponent, Observer
{
public:
    CLASS_DECLARATION(CPUComponent)
        CLASS_DECLARATION(CPUComponent)


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
    void ModifyHealth(const Event& event);
    void ModifyExp(const Event& event);
    void ModifyHeroExp(const Event& event);
    void OnReaction(const Event& event);
    const std::list<std::string>& GetHand() const;
    CardComponent* GetCardComponent(const std::string& cardName);

private:
    std::string playerID = "CPU";

    int m_health = 0;
    int m_exp = 0;
    int m_heroExp = 0;
    bool isActive = false;
    bool isDied = false;

    RivalsArena::eState& gameState;
    Component* m_deck;
    std::list<std::string> m_hand;
public:

    CPUComponent() = default;
};
