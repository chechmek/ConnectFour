#include <iostream>
#include "Player.h"
#include "Playfield.h"

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
		cout << "Player " << signature << " wins!" << endl;
	}
};

class Game {
	playfield field;
	player<playfield> player1;
	player<playfield> player2;
	UI<playfield> ui;
	bool isEnded;
	void checkIfEnd(const playfield& field, char sign) {
		// check if there are 4 connnected
		isEnded = false;
		if (isEnded) {
			ui.show_victory_screen(sign);
		}
	}
	bool placeStone(int col, playfield& field, char sign) {
		
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
	bool play(player<playfield>& player, char signature) {
		int col = player.play(field);
		bool res = placeStone(col, field, signature);
		ui.show_field(field);
		checkIfEnd(field, signature);
		return res;
	}
	void initField() {
		for (int i = 0; i < field.height + 123; ++i) {
			for (int j = 0; j < field.width + 123; ++j) {
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
			moved = false;
			while (!moved)
			{
				moved = play(player2, field.player2);
			}
		}
	}
};

int main()
{
	Game game(1);
	game.Run();
}
