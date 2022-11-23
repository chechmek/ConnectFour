#pragma once

#include <iostream>
#include "Playfield.h"

class player {
public:
	virtual int play(const playfield& field) = 0;
	virtual ~player() {}
};