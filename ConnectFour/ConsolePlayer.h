#pragma once
#include <iostream>
#include "Player.h"

using namespace std;
template<typename F>
struct consoleplayer : public player{
	// returns the column where the player decides to insert his
	// stone
	// F is the playfield which may be any playfield implementing
	// the stoneat method, if you expect a different class because
	// you need methods to verify whether the opponent can win,
	// copy the field into the class that you expect.
	int play(const F& field) {
		int col = -1;
		while (true) {
			cout << "Type in column: ";
			cin >> col;
			--col;
			if (col < 0 || col > field.width - 1) {
				cout << "Try again" << endl;
			}
			else {
				return col;
			}
		}
	}
};
