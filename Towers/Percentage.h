///////////////////////////////////////////////////////////
///// Towers! game - Struct Percentage
///////////////////////////////////////////////////////////

#pragma once
// headers

#include "GameExceptions.h"

struct Percentage {
	Percentage() { Value = 0; }
	Percentage(const unsigned value) {
		if (value > 100)
		{
			throw FailLoadMap("wrong value for Percentage Value");
		}
		Value = value;
	}
	void Edit(const unsigned value) {
		if (value > 100)
		{
			throw FailLoadMap("wrong value for Percentage Value");
		}
		Value = value;
	}
	unsigned Value;
};