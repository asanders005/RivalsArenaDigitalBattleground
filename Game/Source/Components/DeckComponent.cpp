#include "DeckComponent.h"

void DeckComponent::Initialize()
{
}

void DeckComponent::Update(float dt)
{
}

void DeckComponent::Read(const json_t& value)
{
    rapidjson::Value deckvalue = value.FindMember("deck")->value.GetObject();
    DeckData deck;
    READ_DATA_NAME(deckvalue,"starter",deck.starter);
    READ_DATA_NAME(deckvalue,"tier1",deck.tier1);
    READ_DATA_NAME(deckvalue,"tier2",deck.tier2);
    READ_DATA_NAME(deckvalue,"hero",deck.hero);
    for ( const auto& e : deck.starter)
    {
        m_draw.push_back(e);
    }
    for ( const auto& e : deck.tier1)
    {
        m_upgradesConsumable.push_back(e);
    }
    for ( const auto& e : deck.tier2)
    {
        m_upgradesConsumable.push_back(e);
    }
    for ( const auto& e : deck.hero)
    {
        m_upgradesHeroes.push_back(e);
    }
}

void DeckComponent::Write(json_t& value)
{
}