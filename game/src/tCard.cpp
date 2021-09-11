#include "tCard.hpp"

tCard::tCard(tGame::eGuest guest) : m_type(eType::guest), m_value(guest) {};
tCard::tCard(tGame::eRoom room) : m_type(eType::room), m_value(room) {};
tCard::tCard(tGame::eWeapon weapon) : m_type(eType::weapon), m_value(weapon) {};

std::ostream& operator<<(std::ostream& os, const tCard::eType& type) {
    switch(type) {
        case(tCard::eType::guest):
            os << "Guest";
            return os;
        case(tCard::eType::room):
            os << "Room";
            return os;
        case(tCard::eType::weapon):
            os << "Weapon";
            return os;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const tCard& card) {
    switch(card.m_type) {
        case(tCard::eType::guest):
            os << card.m_value.m_guest;
            return os;
        case(tCard::eType::room):
            os << card.m_value.m_room;
            return os;
        case(tCard::eType::weapon):
            os << card.m_value.m_weapon;
            return os;
    }
    return os;
}