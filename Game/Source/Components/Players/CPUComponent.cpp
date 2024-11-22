#include "CPUComponent.h"
#include "DeckComponent.h"
#include "Components/Cards/CardComponent.h"
#include "Framework/GameEventData.h"
#include "Engine.h"

FACTORY_REGISTER(CPUComponent)


void CPUComponent::Initialize()
{
	PlayerComponent::Initialize();

    m_deck = owner->GetComponent<DeckComponent>();

    m_hand = owner->GetComponent<DeckComponent>()->GetHand();
}

void CPUComponent::Update(float dt)
{

}

void CPUComponent::ExecuteTurn()
{
    EvaluateCards(); // Evaluate and sort the hand
    PlayBestCard();
}

void CPUComponent::DrawCard()
{
}

void CPUComponent::DiscardCard(const std::string& cardName)
{
    auto card = owner->scene->GetActor(cardName)->GetComponent<CardComponent>();
    EVENT_NOTIFY_DATA(DiscardCard, new CardDeckIDEventData(card->GetCardID(), card->GetDeckId()));
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
        auto card = owner->scene->GetActor(cardName)->GetComponent<CardComponent>();

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
        std::string& bestcard = m_hand.front();

        auto bestCard = owner->scene->GetActor(bestcard)->GetComponent<CardComponent>();

        if (bestCard->GetCoolDownTimer() == 0) {

            EVENT_NOTIFY_DATA(Play, new CardIDEventData(bestCard->GetCardID()));
            
            DiscardCard(bestcard);
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
    case CardEnums::PlayPhase::START_OF_TURN: score += (gameState == RivalsArena::eState::UPKEEP) ? 5 : -5; break; 
    case CardEnums::PlayPhase::TURN: score += (gameState == RivalsArena::eState::MAIN) ? 5 : -5; break; 
    case CardEnums::PlayPhase::END_OF_TURN: score += (gameState == RivalsArena::eState::END) ? 5 : -5; break; 
    case CardEnums::PlayPhase::PASSIVE: score += 2; break; 
    case CardEnums::PlayPhase::REACTION: score += (gameState == RivalsArena::eState::REACT) ? 8 : -5; break;
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
    EVENT_NOTIFY(EndPlayerTurn);
}



void CPUComponent::React(const Event& event)
{
    auto eventData = dynamic_cast<const TrackerEventData*>(event.data);

    if (this->playerID == eventData->targetPlayer)
    {

        m_heroExp += eventData->changeValue;
    }
}
const std::list<std::string>& CPUComponent::GetHand() const {
    return m_hand;
}

CardComponent* CPUComponent::GetCardComponent(const std::string& cardName)
{
    // Logic to retrieve the CardComponent instance for a given card name
    auto iter = std::find_if(m_hand.begin(), m_hand.end(), [&](const auto& card)
        {
            return card == cardName; // Match by name
        });

    return iter != m_hand.end() ? /* fetch card component */ nullptr : nullptr;
}

void CPUComponent::Read(const json_t& value)
{
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
