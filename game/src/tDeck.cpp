#include "tDeck.hpp"
#include "tGame.hpp"
#include "tCard.hpp"

tDeck::tDeck() {
    for(tGame::eGuest guest : tGame::tGuestIterator()) {
        m_numberOfGuests++;
        push_back(new tCard(guest));
    }
    for(tGame::eRoom room : tGame::tRoomIterator()) {
        m_numberOfRooms++;
        push_back(new tCard(room));
    }
    for(tGame::eWeapon weapon : tGame::tWeaponIterator()) {
        m_numberOfWeapons++;
        push_back(new tCard(weapon));
    }
}