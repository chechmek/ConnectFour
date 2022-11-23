#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include <cstdlib>
#include <Windows.h>

using namespace std;

template<typename F>
struct aiplayer : public player{
private:
	int random_beetwen(int min, int max) {
		return rand() % (max - min + 1) + min;
	}
	struct position {
		int h;
		int w;
		position(int W, int H) {
			w = W;
			h = H;
		}
	};
	int wait_mls = 1000;
	char mysign;
	char enemysign;
	vector<position> get_possible_moves(const F& field) {
		vector<position> possible_moves;
		possible_moves.reserve(7);
		for (int i = 0; i < field.width; ++i) {
			int h = field.height - 1;
			while (true)
			{
				if (field.stoneat(h, i) != field.none) {
					--h;
					continue;
				}
				else {
					position pos(h, i);
					possible_moves.push_back(pos);
					break;
				}
			}
		}
		return possible_moves;
	}
	int get_stone_count(const F& field) {
		int count = 0;
		for (int i = 0; i < field.height; ++i) {
			for (int j = 0; j < field.width; ++j)
				if (field.stoneat(i, j) != field.none) {
					++count;
				}
		}
		return count;
	}
	void define_signs(int stone_count, const F& field) {
		if (stone_count % 2 == 1)
		{
			mysign = field.player2;
			enemysign = field.player1;
		}
		else {
			mysign = field.player1;
			enemysign = field.player2;
		}
	}
	bool is_stone_near(const F& field, int w, int h, char sign) {
		if (field.stoneat(h, w + 1) == sign) // right
			return true;
		if (field.stoneat(h, w - 1) == sign) // left
			return true;
		if (field.stoneat(h + 1, w) == sign) // down
			return true;
		if (field.stoneat(h + 1, w + 1) == sign) // diag right
			return true;
		if (field.stoneat(h + 1, w - 1) == sign) // diag left
			return true;
		return false;
	}
public:
	int play(const F& field) {
		vector<position> possible_moves;
		int move_to_play;
		possible_moves.reserve(7);
		possible_moves = get_possible_moves(field);
		int stone_count = get_stone_count(field);
		if (stone_count < 2) {
			define_signs(stone_count, field);
		}

		while (possible_moves.size() > 1) {
			if (stone_count < 2) {
				Sleep(wait_mls);
				return 3;// middle of map
			}
			for (int i = 0; i < possible_moves.size(); ++i) {
				if (!is_stone_near(field, possible_moves[i].h, possible_moves[i].w, mysign))
				{
					/*cout << endl << "stone count: " << stone_count << endl;
					cout << "possible moves: ";
					for (position pos : possible_moves) {
						cout << "(" << pos.w << "," << pos.h << "), ";
					}
					cout << endl;*/
					possible_moves.erase(possible_moves.begin() + i);
				}

			}
			break;
		}
		move_to_play = random_beetwen(0, possible_moves.size() - 1);
		cout << "decided to play: " << move_to_play;
		Sleep(wait_mls);
		return move_to_play;
	}
};