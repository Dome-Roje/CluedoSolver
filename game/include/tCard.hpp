#pragma once

#include <iostream>
#include <ostream>

#include "tEnumIterator.hpp"
#include "tGame.hpp"

struct tCard {
	enum class eType : unsigned char { guest, room, weapon };
	using tTypeIterator = tEnumIterator<eType, eType::guest, eType::weapon>;
	friend std::ostream &operator<<(std::ostream &os, const tCard::eType &type);

	union uValue {
		tGame::eGuest m_guest;
		tGame::eRoom m_room;
		tGame::eWeapon m_weapon;

		uValue(tGame::eGuest guest) : m_guest(guest) {}
		uValue(tGame::eRoom room) : m_room(room) {}
		uValue(tGame::eWeapon weapon) : m_weapon(weapon) {}
	};

	tCard(tGame::eGuest guest);
	tCard(tGame::eRoom room);
	tCard(tGame::eWeapon weapon);

	eType m_type;
	uValue m_value;

	friend std::ostream &operator<<(std::ostream &os, const tCard &card);
};