#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <vector>
using namespace std;

class game {
	friend ostream& operator<< (ostream&, const game&);
	struct tile {
		bool isHidden {true};
		int item {0}; // -1: mine
	};
	private:
		vector<vector<tile>> board;
	public:
		game(int difficulty); // 0 = beginner, 1 = intermediate, 2 = expert
		void generate(int dimension, int mines);
		bool placeBomb(int x, int y); // returns false if mine already exists
		bool isComplete();
		bool selectTile(int x, int y); // returns false if mine
		void reset(int difficulty);

};

#endif