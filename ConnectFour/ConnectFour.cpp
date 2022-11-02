#include <iostream>
#include "Player.h"
#include "Playfield.h"
#include <vector>

using namespace std;

struct position {
	int h;
	int w;
	position(int W, int H) {
		w = W;
		h = H;
	}
};
struct aiplayer {
private:
	vector<position> get_possible_moves(const playfield& field) {
		vector<position> possible_moves;
		for (int i = 0; i < field.width; ++i) {
			int h = field.height - 1;
			while (true)
			{
				if (field.stoneat(i, h) != field.none) {
					--h;
					continue;
				}
				else {
					position pos(i, h);
					possible_moves.push_back(pos);
				}
			}
		}
	}
public:
	int play(const playfield& field) {
		vector<position> possible_moves;
		possible_moves.reserve(7);
		possible_moves = get_possible_moves(field);
		cout << "possible moves: ";
		for (position pos : possible_moves) {
			cout << "(" << pos.w << "," << pos.h << "), ";
		}
		cout << endl;
		while (possible_moves.size() > 1) {

		}
		cout << "decided to play: " << possible_moves[0].w;
		return possible_moves[0].w;
	}
};


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
	void connectedTests() {
		gamefield testField1;
		for (int i = 0; i < testField1.height; ++i) {
			for (int j = 0; j < testField1.width; ++j) {
				testField1.rep[i][j] = 0;
			}
		}
		testField1.rep[5][0] = 1;
		testField1.rep[5][1] = 1;
		testField1.rep[5][2] = 1;
		testField1.rep[5][3] = 1;
		ui.show_field(testField1);

		bool res = checkIfConnected(testField1, 1);

		cout << res;
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
	bool play(player<gamefield>& player, char signature) {
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
		//connectedTests();
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
			//cout << "field.height: " << field.height << endl;
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
	Game<player<playfield>, player<playfield>, playfield> game(1);
	game.Run();
}
