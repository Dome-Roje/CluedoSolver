#pragma once

#include <string>

#include "tCardHolder.hpp"
#include "tGame.hpp"

struct tPlayer : public tCardHolder {
    std::string m_name;
    tGame* m_game;

    tPlayer(std::string name, tGame& game) : m_name(name), m_game(&game) {}
    tPlayer(tGame& game) : m_name("Jarred"), m_game(&game) {}

    void setNumberOfCards(int numberOfCards) { m_numberOfCards = numberOfCards; }

    virtual tGame::eAction performAction() = 0;
    virtual tGame::tRumor startRumor() = 0;
    virtual tGame::tAccusation makeAccusation() = 0;
    virtual tGame::eRumorResponse respondToRumor() = 0;

    virtual void observeRumorResponse(tGame::tRumor& rumor, tPlayer& respondant, tGame::eRumorResponse response) = 0;
    virtual void observeCard() = 0;
    virtual void observeHand() = 0;

    void die() { alive = false; }
    bool isAlive() { return alive; }

    bool alive { true };
};