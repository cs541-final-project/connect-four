#include <iostream>
#include "environment.h"

Environment::Environment() {
	// Initializes board of row x column dimensions to "E" indicating all states are "empty."
	rows = MAX_ROWS;
	cols = MAX_COLS;
	std::vector<std::vector<char>> temp_board(rows, std::vector<char>(cols, 'E'));
	board = temp_board;
}

Environment::~Environment() {
	// placeholder
}

// Prints current state of environment to console
int Environment::print_board() {
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			std::cout << board[r][c] << " ";
		}
		std::cout << std::endl;
	}
	return EXIT_SUCCESS;
}

// Updates board state with new piece.
// p indicates "color" of piece, c indicates column of placement.
// TODO: Implement penalty upon returning EXIT_FAILURE;
int Environment::place_piece(char p, int c) {
	if (toupper(p) != 'R' && toupper(p) != 'Y') {
		std::cout << "Invalid placement. Piece does not exist.\n";
		exit(EXIT_FAILURE);
	}

	// Checks if the column is full.
	if (board[0][c] != 'E') {
		std::cout << "Column full.\n";
		return EXIT_FAILURE;
	}

	int r = rows - 1;
	while (board[r][c] != 'E' && r > 0)
		r--;

	board[r][c] = p;

	return EXIT_SUCCESS;
}