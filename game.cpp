#include <ctime>
using namespace std;

#include "game.h"

int dimension_v[] = {8, 16, 24};
int mines_v[] = {10, 40, 99};

game::game(int difficulty): dimension(dimension_v[difficulty]) {
	generate(mines_v[difficulty]);
}

game::getDimension() {
	return dimension;
}

void game::generate(int mines) {
	for (int i = 0; i < dimension; ++i) {
		board.push_back(vector<tile>());
		for (int j = 0; j < dimension; ++j) {
			board.back().push_back(tile());
		}
	}
	srand(time(NULL));
	for (int i = 0; i < mines; ++i)
		while (!placeBomb(rand() % dimension, rand() % dimension)) {}
}

bool game::placeBomb(int x, int y) {
	if (board[x][y].item == -1) return false;
	else {
		board[x][y].item = -1;
		for (int i = x - 1; i <= x + 1; ++i)
			for (int j = y - 1; j <= y + 1; ++j) {
				if (i >= 0 and i < dimension and
					j >= 0 and j < dimension) {
					if (board[i][j].item != -1) ++board[i][j].item;
				}
			}
		return true;
	}
}

bool game::isComplete() {
	for (auto& row : board)
		for (auto& column : row)
			if (column.item != -1 and column.isHidden) return false;
	return true;
}

// ASSUME coords are valid and tile is hidden
bool game::selectTile(int x, int y) {
	board[x][y].isHidden = false;
	if (board[x][y].item == 0) clearZeroes(x, y);
	return board[x][y].item != -1;
}

void game::clearZeroes(int x, int y) {
	for (int i = x - 1; i <= x + 1; ++i)
		for (int j = y - 1; j <= y + 1; ++j) {
			if (i >= 0 and i < dimension and
				j >= 0 and j < dimension) {
				if (board[i][j].item == 0 and board[i][j].isHidden == true) {
					board[i][j].isHidden = false;
					clearZeroes(i, j);
				}
				board[i][j].isHidden = false;
			}
		}	
}

void game::reset(int difficulty) {
	for (auto& row : board) row.clear();
	board.clear();
	dimension = dimension_v[difficulty];
	generate(mines_v[difficulty]);
}

ostream& operator<< (ostream& out, const game& that) {
	out << endl << "  ";
	for (int i = 0; i < that.dimension; ++i) out << (i % 10);
	out << endl << "  ";
	for (int i = 0; i < that.dimension; ++i) out << "_";
	out << endl;
	int i = 0;
	for (auto& row : that.board) {
		out << (i % 10) << "|";
		for (auto& column : row) {
			if (column.isHidden) out << "-";
			else out << column.item;
		}
		out << endl;
		++i;
	}
	return out;
}