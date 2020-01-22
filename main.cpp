#include <iostream>
using namespace std;

#include "game.h"

int main() {
	while (true) {
		int difficulty;
		cout << "enter difficulty: ";
		cin >> difficulty;
		game g(difficulty);
		while (!g.isComplete()) {
			int x, y;
			cout << g;
			cout << "choose coordinates: ";
			cin >> x >> y;
			g.selectTile(x, y);
		}
	}
}