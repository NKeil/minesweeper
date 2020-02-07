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
		int dimension;
		vector<vector<tile>> board;
		void clearZeroes(int x, int y);
	public:
		game(int difficulty); // 0 = beginner, 1 = intermediate, 2 = expert
		int getDimension();
		void generate(int mines);
		bool placeBomb(int x, int y); // returns false if mine already exists
		bool isComplete();
		bool selectTile(int x, int y); // returns false if mine
		void reset(int difficulty);

};

#endif