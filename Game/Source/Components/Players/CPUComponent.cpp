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

    if (this) {
        //EventManager::Instance().AddObserver("Upkeep", this, std::bind(&CPUComponent::ExecuteTurn, this, std::placeholders::_1));
    }
	ADD_OBSERVER(ExecuteTurn, CPUComponent::ExecuteTurn);
}

void CPUComponent::Update(float dt)
{
    //Set the Deck and Hand
    //
}

void CPUComponent::ExecuteTurn(const Event& event)
{
    //auto eventData = dynamic_cast<const PlayerStringEventData*>(event.data);
    //if (!eventData) {
    //    std::cerr << "Invalid event data for ExecuteTurn" << std::endl;
    //    return;
    //}

    //if (this->playerID == eventData->targetPlayer) {

    //    EVENT_NOTIFY_DATA(DrawCard, new StringEventData(GetID()));

    //    EvaluateCards();


    //    //std::cout << "Cards in Hand: " << std::endl;
    //    //for (auto cardsInHand : *m_deck->GetHand())
    //    //{

    //    //    std::cout << cardsInHand << std::endl;
    //    //}


    //    PlayBestCard();

    //    //EvaluateAndBuyCard();
    //}

	if (playerID == "CPU")
	{
		for (int i = 0; i < 5; i++)
		{
			float choice = randomf();
			if (choice >= 0.715f)
			{
				EVENT_NOTIFY_DATA(ModifyHealth, new TrackerEventData(playerID, -2));
			}
			else
			{
				EVENT_NOTIFY_DATA(ModifyHealth, new TrackerEventData("player", 1));
			}
		}
		EVENT_NOTIFY(EndTurn);
	}
}

void CPUComponent::DrawCard()
{
    //If needed
}

void CPUComponent::OnDiscardCard(const std::string& cardName)
{

     //EVENT_NOTIFY_DATA(DiscardCard, new CardNameEventData() )
     //EVENT_NOTIFY_DATA(DiscardCard, new CardDeckIDEventData(cardName, GetID()));

}

void CPUComponent::EvaluateCards()
{
    for (std::string cardName : *m_deck->GetHand())
    {
        auto* card = GetCardComponent(cardName);
        if (card)
        {
            EvaluateCardPriority(cardName);
            evaluatedCards.push_back(card);
        }

        EvaluateCardPriority(cardName);
    }

    // Sort cards by priority (descending)
    std::sort(evaluatedCards.begin(), evaluatedCards.end(),
        [](CardComponent* a, CardComponent* b) { return a->GetPriority() > b->GetPriority(); });

    //SortHandByPriority();
}

void CPUComponent::SortHandByPriority()
{
    std::list<std::string>* sort_hand = new std::list<std::string>;
    std::list<std::string>* sort_hand2 = new std::list<std::string>;

    for (std::string cardName : *m_deck->GetHand())
    {
  

        //auto actor = owner->scene->GetActor(cardName);

        //int count = 1;
        //auto& actors = owner->scene->actors;
        //std::cerr << "Available actors: ";
        //for (auto& actor : actors)
        //{
        //    std::cout << " ActorID = " + actor->name << std::endl;
        //    std::cout << " Actor Scene = " + actor->scene->name << std::endl;
        //    std::cout << " Actor Tag = " + actor->tag << std::endl;
        //}

        /*if (!actor) {
            std::cerr << "Actor not found for card: " << cardName << std::endl;
            continue;
        }*/
        auto card = GetCardComponent(cardName);

        if (card->GetPriority() > 0) {

            sort_hand->push_back(cardName);
           
        }
        if (card->GetPriority() == 0)
        {
            continue;
        }

        else {
            sort_hand2->push_back(cardName);
           
        }

    }

    for (std::string cardName : *sort_hand) {
        sort_hand2->push_back(cardName);
        

    }

    my_hand = sort_hand2;
}

void CPUComponent::PlayBestCard()
{
    auto cardlist = m_deck->GetHand();

    std::list<CardComponent*>  cardsPlayed;

    for (auto cardName : *cardlist)
    {
        std::cout << "Played Card: " << cardName << std::endl;

        if (cardName.empty())
        {
            std::cerr << "Error: Card name is empty!" << std::endl;
           
            continue; 
        }

        auto* cards = GetCardComponent(cardName);

        if (cards == nullptr)
        {
            std::cerr << "Error: CardComponent not found for card: " << cardName << std::endl;
           
            continue; 
        }

        if (cards->GetCoolDownTimer() == 0)
        {
            cardsPlayed.push_back(cards);
            //EVENT_NOTIFY_DATA(PlayCard, new CardIDEventData(cards->GetCardID()));

            std::string cardName = cards->GetCardID();
            
            
            continue; 
        }
    }

    if (!cardsPlayed.empty()) {

        for (auto cards : cardsPlayed)
        {
            EVENT_NOTIFY_DATA(PlayCard, new CardIDEventData(cards->GetCardID()));

            EVENT_NOTIFY_DATA(DiscardCard, new CardNameEventData(cards->GetCardID(), cards->GetCardName(), GetID() ));
                
        }
    }
}

int CPUComponent::EvaluateCardPriority(const std::string& cardName)
{
    int score = 0;

    auto* card = GetCardComponent(cardName);

    if (!card || card->GetCardID().empty()) {
        std::cerr << "Invalid or uninitialized CardComponent for actor: " << cardName << std::endl;
        return 0;
    }

        switch (static_cast<CardEnums::CardTier>(card->GetCardTier())) {

        case CardEnums::CardTier::STARTER:
            score += 1;
            break;
        case CardEnums::CardTier::TIER_1:
            score += 3;
            break;
        case CardEnums::CardTier::TIER_2:
            score += 5;
            break;
        case CardEnums::CardTier::HERO:
            score += 10;
            break;
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
            score += 2;
            break;
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
    if (!owner)
    {
        std::cerr << "Error: Owner is null!" << std::endl;
        return nullptr;
    }
    if (!owner->scene)
    {
        std::cerr << "Error: Scene is null!" << std::endl;
        return nullptr;
    }
    auto& listofcards = owner->scene->actors;
    
    for (auto& cards : owner->scene->actors)
    {
        if (cards.get()->GetComponent<CardComponent>())  
        {
            if (cards.get()->GetComponent<CardComponent>()->GetDeckId() == "CPU")
            {
                if (cards.get()->GetComponent<CardComponent>()->GetCardID() == cardName)
                {

                    return cards.get()->GetComponent<CardComponent>();
                }
            }
        }
    }
    return nullptr;
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


