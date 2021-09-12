#pragma once

#include <type_traits>

//! \brief Templated Iterator for enums.
template <typename C, C beginVal, C endVal> class tEnumIterator {
	typedef typename std::underlying_type<C>::type val_t;
	int val;

public:
	tEnumIterator(const C &f) : val(static_cast<val_t>(f)) {}
	tEnumIterator() : val(static_cast<val_t>(beginVal)) {}
	tEnumIterator operator++() {
		++val;
		return *this;
	}
	C operator*() { return static_cast<C>(val); }
	tEnumIterator begin() { return *this; } // default ctor is good
	tEnumIterator end() {
		static const tEnumIterator endIter = ++tEnumIterator(endVal); // cache it
		return endIter;
	}
	bool operator!=(const tEnumIterator &i) { return val != i.val; }
};