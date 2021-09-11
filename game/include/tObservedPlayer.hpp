#pragma once

#include "tPlayer.hpp"

struct tObservedPlayer : public tPlayer {
    tObservedPlayer(std::string name, tGame& game) : tPlayer(name, game) {}
    tObservedPlayer(tGame& game) : tPlayer(game) {}
    tGame::eAction performAction() override { return tGame::getActionInput(); }
    tGame::tRumor startRumor() override { return tGame::getRumorInput(); }
    tGame::tAccusation makeAccusation() override { return tGame::getAccusationInput(); }
    tGame::eRumorResponse respondToRumor() override { return tGame::getRumorResponseInput(); }

    void observeRumorResponse(tGame::tRumor& rumor, tPlayer& respondant, tGame::eRumorResponse response) override {}
    void observeCard() override {};
    void observeHand() override {};
};