#pragma once

#include <vector>
#include <string>
#include <list>
#include "Components/Cards/CardComponent.h"
#include "RivalsArena.h"
#include "PlayerComponent.h"
#include "DeckComponent.h"

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
    float GetHealth();
    float GetExp();
    float GetHeroExp();
    std::string GetID();
    bool GetIsActive();
    bool GetIsDied();

    //Setters
    void SetCPUID(std::string cpuName) { playerID = cpuName; }

    //Functions
    void ExecuteTurn();
    void DrawCard();
    void OnDiscardCard(const std::string& cardName);
    void EvaluateCards();
    void SortHandByPriority();
    void PlayBestCard();
    void SetGameState(RivalsArena::eState* state) { gameState = state; }
    int EvaluateCardPriority(const std::string& cardName);

    //Events
    void EndTurn(const Event& event);

    void OnReact(const Event& event);
    const std::list<std::string>& GetHand();
    class CardComponent* GetCardComponent(const std::string& cardName);

private:
    std::string playerID;

    void React(const Event& event) override;
    const std::list<std::string>& GetHand() const;
    class CardComponent* GetCardComponent(const std::string& cardName);

public:
    std::string playerID;

private:

    float m_health = 0;
    float m_exp = 0;
    float m_heroExp = 0;
    bool isActive = false;
    bool isDied = false;


    RivalsArena::eState* gameState = nullptr;
    Component* m_deck = nullptr;
    std::list<std::string> m_hand;
public:

    CPUComponent() = default;

    RivalsArena::eState gameState;
    class DeckComponent* m_deck;
    std::list<std::string> m_hand;
};

