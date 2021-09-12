#pragma once

//! \brief Any Cluedo entity that holds cards
//! \details Generalisation of a Player to include both the Crime (which holds three cards)
//! and the Pool (which holds the cards that cannot be evenly distributed amongst players).
struct tCardHolder {
	int m_numberOfCards;
};