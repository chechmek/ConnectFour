#include <iostream>
#include "ConsolePlayer.h"
#include "AiPlayer.h"
#include "Playfield.h"
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include "UI.h"
#include "Player.h"

using namespace std;

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
	/*bool play(player& player, char signature) {
		int col = player.play(field);
		bool res = placeStone(col, field, signature);
		ui.show_field(field);
		
		if (checkIfConnected(field, signature)) {
			isEnded = true;
			ui.show_victory_screen(signature);
		}
		return res;
	}*/
	bool play(player& player, char signature) {
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
	Game<consoleplayer<playfield>, aiplayer<playfield>, playfield> game(1);
	game.Run();
}
