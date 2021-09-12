#pragma once

#include <string>

#include "tCardHolder.hpp"
#include "tGame.hpp"

//! \brief Player gameobject that participates in rumors and accusations.
//! \details A Player has a turn in which they perform an action, such as
//! making accusations and starting rumors. They also observe the outcomes
//! of such events.
//! \todo Make deafault player name "Player n".
struct tPlayer : public tCardHolder {
	std::string m_name;
	tGame *m_game; //!< Reference to the game they're part of.

	tPlayer(std::string name, tGame &game) : m_name(name), m_game(&game) {}
	tPlayer(tGame &game) : m_name("Jarred"), m_game(&game) {} //!< Default name to "Jarred"

	void setNumberOfCards(int numberOfCards) { m_numberOfCards = numberOfCards; }

	virtual tGame::eAction performAction() = 0;
	virtual tGame::tRumor startRumor() = 0;
	virtual tGame::tAccusation makeAccusation() = 0;
	virtual tGame::eRumorResponse respondToRumor() = 0;

	//! \brief Handle the broadcast of a rumor response.
	virtual void observeRumorResponse(tGame::tRumor &rumor, tPlayer &respondant,
									  tGame::eRumorResponse response) = 0;
	virtual void observeCard() = 0;
	virtual void observeHand() = 0;

	void die() { alive = false; }
	bool isAlive() { return alive; }

	bool alive{true};
};