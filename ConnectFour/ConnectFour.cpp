#include <iostream>
#include "Player.h"
#include "Playfield.h"

using namespace std;

template<typename F>
class UI {
public:
    void show_field(const F& field) {
        for (int i = 0; i < field.width; ++i) {
            for (int j = 0; i < field.height; ++j) {
                cout << field.stoneat(i, j) << " ";
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
    void checkIfEnd(const playfield &field, char sign) {
        // check if there are 4 connnected
        isEnded = false;
        ui.show_victory_screen(sign);
    }
    void placeStone(int col, playfield& field, char sign) {
        // place into column
    }
    void play(player<playfield> &player, char signature) {
        int col = player.play(field);
        placeStone(col, field, signature);
        ui.show_field(field);
        checkIfEnd(field, signature);
    }
public:
    Game(int a) {
        isEnded = false;
    }
    void Run() {
        ui.show_field(field);
        while (!isEnded) {
            play(player1, field.player1);
            play(player2, field.player2);
        }
    }
};

int main()
{
    Game game(1);
    game.Run();
}
