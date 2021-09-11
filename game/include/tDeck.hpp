#pragma once

#include <vector>

class tCard;

struct tDeck : private std::vector<tCard*> {
    using std::vector<tCard*>::begin;
    using std::vector<tCard*>::end;
    using std::vector<tCard*>::size;

    int m_numberOfGuests = 0;
    int m_numberOfRooms = 0;
    int m_numberOfWeapons = 0;

    tDeck();
};