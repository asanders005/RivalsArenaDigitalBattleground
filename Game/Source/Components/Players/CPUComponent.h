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
    float GetHealth() { return m_health; }
    float GetExp() { return m_exp; }
    float GetHeroExp() { return m_heroExp; }
    std::string GetID() { return playerID; }
    bool GetIsActive() { return isActive; }
    bool GetIsDied() { return isDied; }

    //Setters
    void SetCPUID(std::string cpuName) { playerID = cpuName; }
    void SetDeckComponent(DeckComponent* myDeck) { m_deck = myDeck; my_hand = myDeck->GetHand(); }
    void SetGameState(RivalsArena::eState state) { gameState = state; }
    

    //Functions
    void DrawCard();
    void OnDiscardCard(const std::string& cardName);
    void EvaluateCards();
    void SortHandByPriority();
    void PlayBestCard();
    int EvaluateCardPriority(const std::string& cardName);



    //Events
    void ExecuteTurn(const Event& event);
    void EndTurn(const Event& event);
    void OnReact(const Event& event);
    const std::list<std::string>& GetHand();
    class CardComponent* GetCardComponent(const std::string& cardName);
    void EvaluateAndBuyCard();
    bool HasTierCard();
    CardComponent* FindBestShieldCard();
    int UseSheildCards();
    void DrawSpecficCard();
    void React(const Event& event) override;
    std::vector<CardComponent*> EvaluateCardsComponents();

    //std::string playerID;
private:
    float m_health = 40;
    float m_exp = 0;
    float m_heroExp = 0;
    bool isActive = false;
    bool isDied = false;
    bool isUnderAttack = false;

public:
    CPUComponent() = default;

    RivalsArena::eState gameState = RivalsArena::eState::UPKEEP;
    class DeckComponent* m_deck = nullptr;
    std::vector<CardComponent*> evaluatedCards;
    std::list<std::string>* my_hand;
};

