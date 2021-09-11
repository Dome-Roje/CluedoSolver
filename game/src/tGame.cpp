
#include "tGame.hpp"
#include "tCard.hpp"
#include "tDeck.hpp"
#include "tPlayer.hpp"
#include <iostream>

tGame::tGame() : m_deck(), m_crime() {}

void tGame::start() {
	int numberOfCardsPerPlayer = (m_deck.size() - 3) / m_players.size();
	for (tPlayer *player : m_players) {
		player->setNumberOfCards(numberOfCardsPerPlayer);
		player->observeHand();
	}
	play();
}

void tGame::addPlayer(tPlayer &player) { m_players.push_back(&player); }

tGame::eGuest tGame::getGuestInput() {
	clearScreen();
	int i = 0;
	for (eGuest guest : tGuestIterator()) {
		std::cout << i++ << ": " << guest << std::endl;
	}
	std::cout << "Select Guest: ";
	int inp;
	std::cin >> inp;
	return static_cast<eGuest>((unsigned char)inp);
}

tGame::eRoom tGame::getRoomInput() {
	clearScreen();
	int i = 0;
	for (eRoom room : tRoomIterator()) {
		std::cout << i++ << ": " << room << std::endl;
	}
	std::cout << "Select Room: ";
	int inp;
	std::cin >> inp;
	return static_cast<eRoom>((unsigned char)inp);
}

tGame::eWeapon tGame::getWeaponInput() {
	clearScreen();
	int i = 0;
	for (eWeapon weapon : tWeaponIterator()) {
		std::cout << i++ << ": " << weapon << std::endl;
	}
	std::cout << "Select Weapon: ";
	int inp;
	std::cin >> inp;
	return static_cast<eWeapon>((unsigned char)inp);
}

tGame::eAction tGame::getActionInput() {
	clearScreen();
	int i = 0;
	for (eAction action : tActionIterator()) {
		std::cout << i++ << ": " << action << std::endl;
	}
	int inp;
	std::cin >> inp;
	return static_cast<eAction>((unsigned char)inp);
}

tGame::eRumorResponse tGame::getRumorResponseInput() {
	clearScreen();
	int i = 0;
	for (eRumorResponse response : tRumorResponseIterator()) {
		std::cout << i++ << ": " << response << std::endl;
	}
	int inp;
	std::cin >> inp;
	return static_cast<eRumorResponse>((unsigned char)inp);
}

tGame::tRumor tGame::getRumorInput() {
	return tRumor{getGuestInput(), getRoomInput(), getWeaponInput()};
}

tGame::tAccusation tGame::getAccusationInput() { return getRumorInput(); }

void tGame::clearScreen() {
	for (int i = 0; i < 50; i++)
		std::cout << std::endl;
}

tCard *tGame::getCard() {
	clearScreen();
	int i = 0;
	for (tCard::eType type : tCard::tTypeIterator()) {
		std::cout << i++ << ": " << type << std::endl;
	}
	std::cout << "Select Card Type: ";
	int inp;
	std::cin >> inp;
	tCard::eType type = static_cast<tCard::eType>((unsigned char)inp);
	switch (type) {
	case (tCard::eType::guest): {
		eGuest guest = getGuestInput();
		return getCard(guest);
	}
	case (tCard::eType::room): {
		eRoom room = getRoomInput();
		return getCard(room);
	}
	case (tCard::eType::weapon): {
		eWeapon weapon = getWeaponInput();
		return getCard(weapon);
	}
	}
	return NULL;
}

tCard *tGame::getCard(eGuest &guest) {
	for (tCard *card : m_deck) {
		if (card->m_type == tCard::eType::guest && card->m_value.m_guest == guest)
			return card;
	}
	return NULL;
}

tCard *tGame::getCard(eRoom &room) {
	for (tCard *card : m_deck) {
		if (card->m_type == tCard::eType::room && card->m_value.m_room == room)
			return card;
	}
	return NULL;
}

tCard *tGame::getCard(eWeapon &weapon) {
	for (tCard *card : m_deck) {
		if (card->m_type == tCard::eType::weapon && card->m_value.m_weapon == weapon)
			return card;
	}
	return NULL;
}

void tGame::play() {
	mp_activePlayer = m_players.front();
	while (!m_gameOver) {
		eAction currentAction = mp_activePlayer->performAction();
		while (currentAction != eAction::pass && mp_activePlayer->isAlive()) {
			handlePlayerAction(currentAction);
			currentAction = mp_activePlayer->performAction();
		}
		mp_activePlayer = playerAfter(mp_activePlayer);
	}
}

void tGame::endGame() {
	m_gameOver = true;
	int numberOfAlivePlayers = 0;
	for (tPlayer *player : m_players) {
		if (player->isAlive())
			numberOfAlivePlayers++;
	}
	std::cout << "There are " << numberOfAlivePlayers << " players remaining." << std::endl;
	;
	if (numberOfAlivePlayers == 0) {
		std::cout << "Noone Wins" << std::endl;
		;
	} else {
		std::cout << mp_activePlayer->m_name << " Wins!" << std::endl;
	}
}

tPlayer *tGame::playerAfter(tPlayer *player) {
	if (player == m_players.back())
		return m_players.front();
	return player++;
}

void tGame::handlePlayerAction(eAction &playerAction) {
	switch (playerAction) {
	case (eAction::startRumor):
		handleRumor();
		break;
	case (eAction::makeAccusation):
		handleAccusation();
		break;
	case (eAction::pass):
		break;
	}
}

void tGame::handleRumor() {
	bool rumorResolved = false;
	tRumor rumor = mp_activePlayer->startRumor();
	tPlayer *respondant = playerAfter(mp_activePlayer);
	while (respondant != mp_activePlayer && !rumorResolved) {
		eRumorResponse response = respondant->respondToRumor();
		switch (response) {
		case (eRumorResponse::disprove):
			rumorResolved = true;
			mp_activePlayer->observeCard();
			break;
		case (eRumorResponse::pass):
			break;
		case (eRumorResponse::stop):
			return;
		}
		broadcastRumorResponse(rumor, *respondant, response);
		respondant = playerAfter(respondant);
	}
}

void tGame::handleAccusation() {
	tAccusation accusation = mp_activePlayer->makeAccusation();
	bool accusationIsCorrect = false;
	if (accusationIsCorrect) {
		endGame();
	} else {
		killPlayer(*mp_activePlayer);
	}
}

void tGame::killPlayer(tPlayer &player) {
	player.die();
	int numberOfAlivePlayers = 0;
	for (tPlayer *player : m_players) {
		if (player->isAlive())
			numberOfAlivePlayers++;
	}
	if (numberOfAlivePlayers == 0)
		endGame();
}

void tGame::broadcastRumorResponse(tRumor &rumor, tPlayer &respondant, eRumorResponse &response) {
	for (tPlayer *player : m_players) {
		player->observeRumorResponse(rumor, respondant, response);
	}
}

std::ostream &operator<<(std::ostream &os, const tGame::eGuest &guest) {
	switch (guest) {
	case (tGame::eGuest::green):
		os << "Green";
		return os;
	case (tGame::eGuest::mustard):
		os << "Mustard";
		return os;
	case (tGame::eGuest::peacock):
		os << "Peacock";
		return os;
	case (tGame::eGuest::plum):
		os << "Plum";
		return os;
	case (tGame::eGuest::scarlet):
		os << "Scarlet";
		return os;
	case (tGame::eGuest::white):
		os << "White";
		return os;
	}
	return os;
}
std::ostream &operator<<(std::ostream &os, const tGame::eRoom &room) {
	switch (room) {
	case (tGame::eRoom::diningRoom):
		os << "Dining Room";
		return os;
	case (tGame::eRoom::guestHouse):
		os << "Guest House";
		return os;
	case (tGame::eRoom::hall):
		os << "Hall";
		return os;
	case (tGame::eRoom::kitchen):
		os << "Kitchen";
		return os;
	case (tGame::eRoom::livingRoom):
		os << "Living Room";
		return os;
	case (tGame::eRoom::observatory):
		os << "Observatory";
		return os;
	case (tGame::eRoom::patio):
		os << "Patio";
		return os;
	case (tGame::eRoom::spa):
		os << "Spa";
		return os;
	case (tGame::eRoom::theatre):
		os << "Theatre";
		return os;
	}
	return os;
}
std::ostream &operator<<(std::ostream &os, const tGame::eWeapon &weapon) {
	switch (weapon) {
	case (tGame::eWeapon::axe):
		os << "Axe";
		return os;
	case (tGame::eWeapon::bat):
		os << "Bat";
		return os;
	case (tGame::eWeapon::candlestick):
		os << "Candlestick";
		return os;
	case (tGame::eWeapon::dumbbell):
		os << "Dumbbell";
		return os;
	case (tGame::eWeapon::knife):
		os << "Knife";
		return os;
	case (tGame::eWeapon::pistol):
		os << "Pistol";
		return os;
	case (tGame::eWeapon::poison):
		os << "Poison";
		return os;
	case (tGame::eWeapon::rope):
		os << "Rope";
		return os;
	case (tGame::eWeapon::trophy):
		os << "Tropy";
		return os;
	}
	return os;
}
std::ostream &operator<<(std::ostream &os, const tGame::eAction &action) {
	switch (action) {
	case (tGame::eAction::makeAccusation):
		os << "Make Accusation";
		return os;
	case (tGame::eAction::pass):
		os << "Pass";
		return os;
	case (tGame::eAction::startRumor):
		os << "Start Rumor";
		return os;
	}
	return os;
}
std::ostream &operator<<(std::ostream &os, const tGame::eRumorResponse &response) {
	switch (response) {
	case (tGame::eRumorResponse::disprove):
		os << "Disprove Rumor";
		return os;
	case (tGame::eRumorResponse::pass):
		os << "Pass";
		return os;
	case (tGame::eRumorResponse::stop):
		os << "Rumor Stays Unanswered";
		return os;
	}
	return os;
}