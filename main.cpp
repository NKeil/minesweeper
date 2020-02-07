#include <iostream>
#include <ctime>
using namespace std;

#include "game.h"

int main() {
	vector<string> win_messages{
		"wow, you won. that is good.",
		"excellent. you are a winner. i am congradulating you.",
		"you have finished the game. and you have won. that is good.",
		"this is a game. this game has been won by you.",
		"oh. the game is over. why did the game end? let me read the report. oh. you won. okay."
	};
	while (true) {
		int dif;
		cout << "enter difficulty[0-2]: ";
		cin >> dif;
		game g(dif);
		int dim = g.getDimension();
		while (!g.isComplete()) {
			int x, y;
			cout << g;
			cout << "enter coordinates [0," << dim - 1 << "]x[0," << dim - 1 <<"]" << endl;
			cout << "(ex: \"2 3\"): ";
			cin >> x >> y;
			if (x < 0 or x >= dim or y < 0 or y >= dim)
				cout << "invalid coordinates!" << endl;
			if (!g.selectTile(x, y)) {
				cout << "you have selected a bomb and you have " << endl;
				cout << "blown up and you have died, unfortunately" << endl;
				break;
			}
		}
		if (g.isComplete()) {
			srand(time(NULL));
			cout << win_messages[rand() % win_messages.size()] << endl;
		}
		char response;
		cout << "try again? (y/n): ";
		cin >> response;
		if (response != 'y' and response != 'Y') break;
	}
}