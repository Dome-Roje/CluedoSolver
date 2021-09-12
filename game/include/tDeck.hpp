#pragma once

#include <vector>

class tCard;

//! \brief Container for card pointers used in the game.
//! \details Extends a vector of tCard pointers to note the
//! number of guest, room, and weapon cards. Order of cards always
//! remains the same.
//! \todo Implement tDeck[] access to implement fast-search by using the order
//! of cards and number of guests/rooms/weapons.
struct tDeck : private std::vector<tCard *> {
	using std::vector<tCard *>::begin;
	using std::vector<tCard *>::end;
	using std::vector<tCard *>::size;

	int m_numberOfGuests{0};
	int m_numberOfRooms{0};
	int m_numberOfWeapons{0};

	//! \brief Initialise the deck by filling it with all the cards.
	tDeck();
};