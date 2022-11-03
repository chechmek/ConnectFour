#include <iostream>
#include "Player.h"
#include "Playfield.h"
#include <vector>
#include <Windows.h>
#include <cstdlib>

using namespace std;

template<typename F>
class UI {
public:
	void show_field(const F& field) {
		system("cls");
		for (int i = 0; i < field.height; ++i) {
			for (int j = 0; j < field.width; ++j) {
				cout << (int)field.rep[i][j] << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < field.width; ++i) {
			cout << i + 1 << " ";
		}
	}
	void show_victory_screen(char signature) {
		cout << "Player " << (int)signature << " wins!" << endl;
	}
};

template<typename F>
struct aiplayer{
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
			for(int j = 0; j < field.width; ++j)
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
		if (field.stoneat(h+1, w) == sign) // down
			return true;
		if (field.stoneat(h+1, w + 1) == sign) // diag right
			return true;
		if (field.stoneat(h+1, w - 1) == sign) // diag left
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

template<typename fplayer, typename splayer, typename gamefield>
class Game {
	gamefield field;
	fplayer player1;
	splayer player2;
	UI<gamefield> ui;
	bool isEnded;
	bool checkIfConnected(const gamefield& f, char sign) {
		for (int i = 0; i < f.height; ++i) {
			for (int j = 0; j < f.width; ++j) {
				if (f.stoneat(i, j) == f.none)
					continue;
				
				if (connectedRight(f, i, j, f.stoneat(i, j)))
					return true;
				if (connectedDown(f, i, j, f.stoneat(i, j)))
					return true;
				if (connectedDiagonalRight(f, i, j, f.stoneat(i, j)))
					return true;
				if (connectedDiagonalLeft(f, i, j, f.stoneat(i, j)))
					return true;
			}
		}
		return false;
	}
	bool connectedRight(const gamefield& f, int h, int w, char sign) {
		for (int i = w; i < w + 4; ++i) {
			if (f.stoneat(h, i) != sign)
				return false;
		}
		return true;
	}
	bool connectedDown(const gamefield& f, int h, int w, char sign) {

		for (int i = h; i < h + 4; ++i) {
			if (f.stoneat(i, w) != sign)
				return false;
		}
		return true;
	}
	bool connectedDiagonalRight(const gamefield& f, int h, int w, char sign) {
		for (int i = 0; i < 4; ++i) {
			if (f.stoneat(h + i, w + i) != sign)
				return false;
		}
		return true;
	}
	bool connectedDiagonalLeft(const gamefield& f, int h, int w, char sign) {
		for (int i = 0; i < 4; ++i) {
			if (f.stoneat(h + i, w - i) != sign)
				return false;
		}
		return true;
	}
	bool placeStone(int col, gamefield& field, char sign) {
		
		int yPos = -1;
		for (int y = 0; y < field.height; ++y) {
			if (y > field.height - 1)
				return false;
			yPos = field.height - 1 - y;
			if (field.stoneat(yPos, col) == field.none) {
				cout << field.stoneat(4, 6);
				field.rep[yPos][col] = sign;
				cout << field.rep[4,6] << ", " << field.rep[5, 0] << endl;
				return true;
			}
		}
	}
	bool play(fplayer& player, char signature) {
		int col = player.play(field);
		bool res = placeStone(col, field, signature);
		ui.show_field(field);
		
		if (checkIfConnected(field, signature)) {
			isEnded = true;
			ui.show_victory_screen(signature);
		}
		return res;
	}
	bool play(splayer& player, char signature) {
		int col = player.play(field);
		bool res = placeStone(col, field, signature);
		ui.show_field(field);

		if (checkIfConnected(field, signature)) {
			isEnded = true;
			ui.show_victory_screen(signature);
		}
		return res;
	}
	void initField() {
		for (int i = 0; i < field.width; ++i) {
			for (int j = 0; j < field.height; ++j) {
				field.rep[i][j] = 0;
			}
		}
	}
public:
	Game(int a) {
		initField();
		isEnded = false;
	}
	void Run() {
		bool moved;
		ui.show_field(field);
		
		while (!isEnded) {
			/*int a = 1;
			field.rep[1][1] = 't';
			ui.show_field(field);
			cin >> a;*/
			moved = false;
			while (!moved)
			{
				moved = play(player1, field.player1);
			}
			if (isEnded)
				break;
			moved = false;
			while (!moved)
			{
				moved = play(player2, field.player2);
			}
			/*cout << field.stoneat(4, 6) << ", " << field.stoneat(5, 0) << endl;
			field.rep[5][0] = 3;
			cout << field.stoneat(4, 6) << ", " << field.stoneat(5,0) << endl;*/
		}
	}
};

int main()
{
	Game<player<playfield>, aiplayer<playfield>, playfield> game(1);
	game.Run();
}
