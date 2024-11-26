#include "CPUComponent.h"
#include "DeckComponent.h"
#include "Components/Cards/CardComponent.h"
#include "Framework/GameEventData.h"
#include "Engine.h"

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
  
    m_deck = owner->GetComponent<DeckComponent>(playerID);

    m_hand = m_deck->GetHand();
}

void CPUComponent::Update(float dt)
{

}

void CPUComponent::ExecuteTurn()
{
    EvaluateCards(); // Evaluate and sort the hand
    PlayBestCard();//Play the best card
}

void CPUComponent::DrawCard()
{
    //If needed
}

void CPUComponent::OnDiscardCard(const std::string& cardName)
{
    auto card = GetCardComponent(cardName);


    EVENT_NOTIFY_DATA(DiscardCard, new CardNameEventData(card->GetCardID(), cardName, card->GetDeckId()));
}

void CPUComponent::EvaluateCards()
{
    for (std::string cardName : m_hand)
    {
        EvaluateCardPriority(cardName);
    }

    SortHandByPriority();
}

void CPUComponent::SortHandByPriority()
{
    std::list<std::string> sort_hand;
    std::list<std::string> sort_hand2;

    for (std::string cardName : m_hand)
    {
        auto card = GetCardComponent(cardName);

        if (card->GetPriority() >= 0) {
            sort_hand.push_back(card->GetCardName());
        }
        else {
            sort_hand2.push_back(card->GetCardName());
        }

    }

    for (std::string cardName : sort_hand) {
        sort_hand2.push_back(cardName);
    }

    m_hand = sort_hand2;
}

void CPUComponent::PlayBestCard()
{
    if (!m_hand.empty()) {
        std::string bestcardname = m_hand.front();

        auto bestCard = GetCardComponent(bestcardname);

        if (bestCard->GetCoolDownTimer() == 0) {

            EVENT_NOTIFY_DATA(Play, new CardIDEventData(bestCard->GetCardID()));

            OnDiscardCard(bestcardname);
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


        m_heroExp += eventData->changeValue;
    }


}
const std::list<std::string>& CPUComponent::GetHand()
{
    return m_hand;
}

CardComponent* CPUComponent::GetCardComponent(const std::string& cardName)
{
    auto card = this->owner->GetComponent<CardComponent>(cardName);

    return card;
}

void CPUComponent::EvaluateAndBuyCard()
{
    std::list<std::string> heroes = m_deck->GetHeroes();
    std::list<std::string> upgradeConusmables = m_deck->GetUpgradeConsumables();
    std::list<std::string> upgradedHeroes = m_deck->GetUpgradeHeroes();

    std::string bestHeroToBuy;
    std::string bestUpgradedHeroToBuy;
    std::string bestUpgradedConsumablesToBuy;

    int highestPriority = -1;

    for (const auto& heroName : heroes)
    {
        int priority = EvaluateCardPriority(heroName);

        if (priority > highestPriority)
        {
            highestPriority = priority;
            bestHeroToBuy = heroName;
        }
    }

    for (const auto& upHeroesName : upgradedHeroes)
    {
        int priority = EvaluateCardPriority(upHeroesName);

        if (GetCardComponent(upHeroesName)->GetCardTier() == CardEnums::CardTier::TIER_2 && !HasTierCard())
        {
            continue;
        }

        if (priority > highestPriority)
        {
            highestPriority = priority;
            bestUpgradedHeroToBuy = upHeroesName;
        }
    }
    
    for (const auto& upConusmables : upgradeConusmables)
    {

        int priority = EvaluateCardPriority(upConusmables);

        if (GetCardComponent(upConusmables)->GetCardTier() == CardEnums::CardTier::TIER_2 && !HasTierCard())
        {
            continue;
        }

        if (priority > highestPriority)
        {
            highestPriority = priority;
            bestUpgradedConsumablesToBuy = upConusmables;
        }

    }
}

bool CPUComponent::HasTierCard()
{
    for (const auto& cardName : m_hand)
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

    for (const auto& cardName : m_hand)
    {
        auto card = GetCardComponent(cardName);
        if (card && card->GetPlayPhase() == CardEnums::PlayPhase::REACTION)
        {
            if (card->GetIsDefensive()) {
                /*if (card.defense > highestDefense)
                {
                    highestDefense = defense;
                    bestShield = card;
                }*/
            }

        }
    }
    return bestShield;
}

void CPUComponent::HandleReactPhase()
{
    if (!isUnderAttack) return;

    int mitigatedDamage = 10;

    auto shieldCard = FindBestShieldCard();
    if (shieldCard)
    {
        //Change get the sheild card
        //mitigatedDamage -= shieldCard->GetDefenseValue();
        mitigatedDamage = std::max(0, mitigatedDamage);
        CPUComponent::OnDiscardCard(shieldCard->GetCardName());
    }
    m_health -= mitigatedDamage;

    // Notify the attacker about the damage received by the CPU
    //EVENT_NOTIFY_DATA(DamageDealt, new TrackerEventData{ m_playerID, mitigatedDamage });

    // Reset attack flags
    isUnderAttack = false;
}


