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

template<typename F>
class PlayerFactory {
private:
	vector<string> player_types{ "You(console input)", "Romans ai player" };
public:
	void show_types() {
		for (int i = 0; i < player_types.size(); ++i)
			cout << i + 1 << ". " << player_types[i] << endl;
	}
	player* get_player(int i) {
		switch (i)
		{
		case 1:
			return new consoleplayer<F>();
		case 2:
			return new aiplayer<F>();
		default:
			break;
		}
	}
};

template<typename gamefield>
class Game {
	gamefield field;
	player& player1;
	player& player2;
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
	Game(player &pl1, player &pl2) 
		: player1(pl1), player2(pl2) {
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
	int i1;
	int i2;
	PlayerFactory<playfield> factory;

	factory.show_types();
	cout << "Select first player" << endl;
	cin >> i1;
	cout << "Select second player" << endl;
	cin >> i2;

	Game<playfield> game(*factory.get_player(i1), *factory.get_player(i2));
	game.Run();
}
