#include <random>
using namespace std;

#include "game.h"

random_device dev;
mt19937 rng(dev());
int dimension_v[] = {8, 16, 24};
int mines_v[] = {10, 40, 99};

game::game(int difficulty) {
	generate(dimension_v[difficulty], mines_v[difficulty]);
}

void game::generate(int dimension, int mines) {
	for (int i = 0; i < dimension; ++i) {
		board.push_back(vector<tile>());
		for (int j = 0; j < dimension; ++j) {
			board.back().push_back(tile());
		}
	}
	uniform_int_distribution<mt19937::result_type> dist6(0, dimension - 1);
	for (int i = 0; i < mines; ++i)
		while (!placeBomb(dist6(rng), dist6(rng))) {}
}

bool game::placeBomb(int x, int y) {
	if (board[x][y].item == -1) return false;
	else {
		board[x][y].item = -1;
		for (int i = x - 1; i < x + 2; ++i)
			for (int j = y - 1; j < y + 2; ++j) {
				if (i >= 0 and i < board.size() and
					j >= 0 and j < board.size()) {
					if (board[i][j].item != -1) ++board[i][j].item;
				}
			}
		return true;
	}
}

bool game::isComplete() {
	for (auto& row : board)
		for (auto& column : row)
			if (column.isHidden) return false;
	return true;
}

// ASSUME coords are valid and tile is hidden
bool game::selectTile(int x, int y) {
	board[x][y].isHidden = false;
	return board[x][y].item != -1;
}

void game::reset(int difficulty) {
	for (auto& row : board) row.clear();
	board.clear();
	generate(dimension_v[difficulty], mines_v[difficulty]);
}

ostream& operator<< (ostream& out, const game& that) {
	out << "board:" << endl;
	for (auto& row : that.board) {
		for (auto& column : row) {
			if (column.isHidden) out << "X";
			else out << column.item;
		}
		out << endl;
	}
	return out;
}