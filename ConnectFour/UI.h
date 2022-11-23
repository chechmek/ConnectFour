#pragma once

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