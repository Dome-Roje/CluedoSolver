#pragma once

#include <iostream>

#include "tCrime.hpp"
#include "tDeck.hpp"
#include "tEnumIterator.hpp"

class tPlayer;

//! \brief Cluedo game-logic.
//! \details The structure defining all game objects such as
//! the Guests, Rooms, Weapons. It also contains the players, the cards they use as well
//! as the crime.
class tGame {
public:
	enum class eGuest : unsigned char { green, mustard, peacock, plum, scarlet, white };
	using tGuestIterator = tEnumIterator<eGuest, eGuest::green, eGuest::white>;
	friend std::ostream &operator<<(std::ostream &os, const tGame::eGuest &guest);

	enum class eRoom : unsigned char {
		diningRoom,
		guestHouse,
		hall,
		kitchen,
		livingRoom,
		observatory,
		patio,
		spa,
		theatre
	};
	using tRoomIterator = tEnumIterator<eRoom, eRoom::diningRoom, eRoom::theatre>;
	friend std::ostream &operator<<(std::ostream &os, const tGame::eRoom &room);

	enum class eWeapon : unsigned char {
		axe,
		bat,
		candlestick,
		dumbbell,
		knife,
		pistol,
		poison,
		rope,
		trophy
	};
	using tWeaponIterator = tEnumIterator<eWeapon, eWeapon::axe, eWeapon::trophy>;
	friend std::ostream &operator<<(std::ostream &os, const tGame::eWeapon &weapon);

	enum class eAction : unsigned char { makeAccusation, pass, startRumor };
	using tActionIterator = tEnumIterator<eAction, eAction::makeAccusation, eAction::startRumor>;
	friend std::ostream &operator<<(std::ostream &os, const tGame::eAction &action);

	enum class eRumorResponse : unsigned char { disprove, pass, stop };
	using tRumorResponseIterator =
		tEnumIterator<eRumorResponse, eRumorResponse::disprove, eRumorResponse::stop>;
	friend std::ostream &operator<<(std::ostream &os, const tGame::eRumorResponse &response);

	struct tRumor {
		eGuest m_guest;
		eRoom m_room;
		eWeapon m_weapon;
	};
	using tAccusation = tRumor;

	bool m_gameOver{false};

	tDeck m_deck;
	std::vector<tPlayer *> m_players;
	tCrime m_crime;

	tGame();
	void start(); //!< Public call to start the game. Runs the main loop.
	void addPlayer(tPlayer &player);

	static eGuest getGuestInput();
	static eRoom getRoomInput();
	static eWeapon getWeaponInput();
	static eAction getActionInput();
	static eRumorResponse getRumorResponseInput();
	static tRumor getRumorInput();
	static tAccusation getAccusationInput();
	static void clearScreen();

	tCard *getCard();
	tCard *getCard(eGuest &guest);
	tCard *getCard(eRoom &room);
	tCard *getCard(eWeapon &weapon);

private:
	void play(); //!< Game mainloop.
	void endGame();
	void killPlayer(tPlayer &player);
	void broadcastRumorResponse(tRumor &rumor, tPlayer &respondant, eRumorResponse &response);
	void handlePlayerAction(eAction &playerAction);
	void handleRumor();
	void handleAccusation();
	tPlayer *playerAfter(tPlayer *player);

	tPlayer *mp_activePlayer;
};