#include "CPUComponent.h"
#include "DeckComponent.h"
#include "Components/Cards/CardComponent.h"
#include "Framework/GameEventData.h"
#include "Engine.h"

#include <algorithm>
#include <iostream>
#include <typeinfo>

FACTORY_REGISTER(CPUComponent);


void CPUComponent::Read(const json_t& value)
{
    CPUComponent::Initialize();

    READ_DATA(value, playerID);
    READ_DATA(value, m_health);
    READ_DATA(value, m_exp);
    READ_DATA(value, m_heroExp);
    READ_DATA(value, isActive);
    READ_DATA(value, isDied);
}

void CPUComponent::Write(json_t& value)
{
}

void CPUComponent::Initialize()
{
	PlayerComponent::Initialize();
    //ADD_OBSERVER(CpuUpkeep, CPUComponent::ExecuteTurn);

}

void CPUComponent::Update(float dt)
{

}

void CPUComponent::ExecuteTurn(const Event& event)
{

    auto eventData = dynamic_cast<const TrackerEventData*>(event.data);
    if (this->playerID == eventData->targetPlayer)
    {
        EvaluateCards(); // Evaluate and sort the hand
        PlayBestCard();//Play the best card
        EvaluateAndBuyCard();        
    }

}

void CPUComponent::DrawCard()
{
    //If needed
}

void CPUComponent::OnDiscardCard(const std::string& cardName)
{
     auto card = GetCardComponent(cardName);

     EVENT_NOTIFY_DATA(DiscardCard, new CardDeckIDEventData(card->GetCardID(), GetID()));

     
}

void CPUComponent::EvaluateCards()
{
    for (std::string cardName : *my_hand)
    {
        EvaluateCardPriority(cardName);
    }

    SortHandByPriority();
}

void CPUComponent::SortHandByPriority()
{
    std::list<std::string>* sort_hand{};
    std::list<std::string>* sort_hand2{};

    for (std::string cardName : *my_hand)
    {
        auto card = GetCardComponent(cardName);

        if (card->GetPriority() >= 0) {

            sort_hand->push_back(cardName);
            //sort_hand.push_back(card->GetCardName());
        }
        else {
            sort_hand2->push_back(cardName);
            //sort_hand2.push_back(card->GetCardName());
        }

    }

    for (std::string cardName : *sort_hand) {
        sort_hand2->push_back(cardName);
        //sort_hand2.push_back(cardName);

    }

    my_hand = sort_hand2;
}

void CPUComponent::PlayBestCard()
{
    bool isEmpty = my_hand->empty();

    while (!my_hand->empty())
{
    for (std::string cardNames : *my_hand)
    {
        auto cards = GetCardComponent(cardNames);

        if (cards->GetCoolDownTimer() == 0) //Check if they can play ir
        {
            EVENT_NOTIFY_DATA(Play, new CardIDEventData(cards->GetCardID()));

            OnDiscardCard(cardNames);
        }
    }
}
}

int CPUComponent::EvaluateCardPriority(const std::string& cardName)
{
    int score = 0;

    auto card = owner->scene->GetActor(cardName)->GetComponent<CardComponent>();
    //if (owner->GetComponent<PlayerComponent>().id == data->get()->playerID)

    // Priority logic (similar to the standalone function)
    switch (card->GetCardTier()) {
    case CardEnums::CardTier::STARTER: score += 1; break;
    case CardEnums::CardTier::TIER_1: score += 3; break;
    case CardEnums::CardTier::TIER_2: score += 5; break;
    case CardEnums::CardTier::HERO: score += 10; break;
    }
	
    // Phase-specific priorities
    switch (card->GetPlayPhase()) {
    case CardEnums::PlayPhase::START_OF_TURN:
        if (gameState == RivalsArena::eState::UPKEEP)
        {
            score += 5;
        }
        else {
            score += -5;
        }
        break;
    case CardEnums::PlayPhase::TURN:
        if (gameState == RivalsArena::eState::MAIN)
        {
            score += 5;
        }
        else {
            score += -5;
        }
        break;
    case CardEnums::PlayPhase::END_OF_TURN:
        if (gameState == RivalsArena::eState::END)
        {
            score += 5;
        }
        else {
            score += -5;
        }
        break;
    case CardEnums::PlayPhase::PASSIVE:
        score += 2; break;
    case CardEnums::PlayPhase::REACTION:
        if (gameState == RivalsArena::eState::REACT)
        {
            score += 8;
        }
        else {
            score += -5;
        }
        break;
    }

    // Defensive cards have higher priority when under attack
    if (card->GetIsDefensive() && gameState == RivalsArena::eState::REACT) {
        score += 7;
    }

    // Optional cards have lower priority if actions are limited
    if (card->GeTIsOptional()) {
        score -= 3;
    }

    // Example: Targeting a specific player
    if (card->GetTargetPlayer() && card->GetCoolDown() == 0) { //Check if card has target player
        score += 2;
    }
    card->SetProity(score);

    // Add more evaluation logic here based on state, phase, etc.
    return score;
}

void CPUComponent::EndTurn(const Event& event)
{
	
}



void CPUComponent::OnReact(const Event& event)
{   

}

void CPUComponent::React(const Event& event)

{
    auto eventData = dynamic_cast<const TrackerEventData*>(event.data);

    if (this->playerID == eventData->targetPlayer)
    {
	    int migatedDamage = UseSheildCards();
	    m_heroExp += eventData->changeValue - migatedDamage;
    }


}

CardComponent* CPUComponent::GetCardComponent(const std::string& cardName)
{
    auto card = this->owner->GetComponent<CardComponent>(cardName);

    return card;
}

void CPUComponent::EvaluateAndBuyCard()
{
    std::list<std::string>* heroes = m_deck->GetHeroes();
    std::list<std::string>* upgradeConusmables = m_deck->GetUpgradeConsumables();
    std::list<std::string>* upgradedHeroes = m_deck->GetUpgradeHeroes();

    std::string bestHeroToBuy;
    std::string bestUpgradedHeroToBuy;
    std::string bestUpgradedConsumablesToBuy;

    int highestPriority = -1;
    CardComponent* heroCardBuy{};
    CardComponent* consumablesToBuy;
    CardComponent* upgradedHeroToBuy;


    for (auto heroName : *heroes)
    {
        int priority = EvaluateCardPriority(heroName);

        if (priority > highestPriority)
        {
            highestPriority = priority;
            bestHeroToBuy = heroName;

            heroCardBuy = GetCardComponent(bestHeroToBuy);
        }
    }
    for (auto consumablesName : *upgradeConusmables)
    {
        int priority = EvaluateCardPriority(consumablesName);

        if (priority > highestPriority)
        {
            highestPriority = priority;
            bestUpgradedConsumablesToBuy = consumablesName;

            consumablesToBuy = GetCardComponent(bestUpgradedConsumablesToBuy);
        }
    }

    for (auto consumablesName : *upgradedHeroes)
    {
        int priority = EvaluateCardPriority(consumablesName);

        if (priority > highestPriority)
        {
            highestPriority = priority;
            bestUpgradedHeroToBuy = consumablesName;

            upgradedHeroToBuy = GetCardComponent(bestUpgradedConsumablesToBuy);
        }
    }

    if (heroCardBuy)
    {

        //EVENT_NOTIFY_DATA(DrawSpecficCard, new CardIDEventData(heroCardBuy->GetCardID()));


    }

    if (!bestUpgradedConsumablesToBuy.empty())
    {

    }

    if (!bestUpgradedHeroToBuy.empty())
    {

    }

}

bool CPUComponent::HasTierCard()
{
    for (const auto& cardName : *my_hand)
    {
        auto card = GetCardComponent(cardName);
        if (card && card->GetCardTier() == CardEnums::CardTier::TIER_1)
        {
            return true;
        }
    }
    return false;
}

CardComponent* CPUComponent::FindBestShieldCard()
{
    CardComponent* bestShield = nullptr;
    int highestDefense = 0;
    bool ifAny = false;

    for (const auto& cardName : *my_hand)
    {
        auto card = GetCardComponent(cardName);
        if (card && card->GetPlayPhase() == CardEnums::PlayPhase::REACTION)
        {
            if (card->GetIsDefensive()) 
            {
                /*if (card.defense > highestDefense)
                {
                    highestDefense = defense;
                    bestShield = card;
                }*/

                ifAny = true;
            }

        }
    }
    if (!ifAny)
    {
        return nullptr;
    }
    
    return bestShield;
}


int CPUComponent::UseSheildCards()
{
    int mitigatedDamage = 0;

    if (!isUnderAttack)
    {
        return 0;
    }

    if (FindBestShieldCard() == nullptr)
    {
        return 0;
    }

    auto shieldCard = FindBestShieldCard();
    if (shieldCard)
    {
        //Change get the sheild card
        //mitigatedDamage -= shieldCard->GetDefenseValue();
        
        CPUComponent::OnDiscardCard(shieldCard->GetCardName());
    }

    // Notify the attacker about the damage received by the CPU
    //EVENT_NOTIFY_DATA(DamageDealt, new TrackerEventData{ m_playerID, mitigatedDamage });

    // Reset attack flags
    isUnderAttack = false;

    return mitigatedDamage;
}

void CPUComponent::DrawSpecficCard()
{
    //std::string cardName = owner->GetComponent<DeckComponent>(m_deckID)->GetDrawHand()->back();

    //std::string cardID;
    //bool containsID = true;
    //do
    //{
    //    int idNum = random(10);
    //    cardID = m_deckID + "_Card" + std::to_string(idNum);

    //    auto iter = std::find(m_hand.begin(), m_hand.end(), cardID);

    //    if (iter == m_hand.end()) containsID = false;
    //} while (containsID);

    //m_hand.push_back(cardID);

    //if (auto card = Factory::Instance().Create<Actor>(cardName))
    //{
    //    card->transform.position = { Vector2{ i * 180.0f + 70, 600.0f } };
    //    card->GetComponent<CardComponent>()->SetCardID(cardID);
    //    card->GetComponent<CardComponent>()->SetDeckID(cardID);

    //    owner->scene->AddActor(std::move(card), true);

    //    std::cout << "Drawing Card: " << cardName << std::endl;
    //}
}


