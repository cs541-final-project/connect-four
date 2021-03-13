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
	if (toupper(p) != 'R' && toupper(p) != 'B') {
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

// Checks rows of the environment to determine if a color won
// I.E. Has 4 pieces in a row, either vertically, horizontally, or diagonally.
int Environment::has_won(char color) {

	// Checks horizontal
	for (int r = 0; r < rows; ++r) {
		for (int c = 3; c < cols; ++c) {
			char c1 = board[r][c - 3];
			char c2 = board[r][c - 2];
			char c3 = board[r][c - 1];
			char c4 = board[r][c];
			if (c1 == c2 && c2 == c3 && c3 == c4 && c4 == color)
				return EXIT_SUCCESS;
		}
	}

	// Checks verticle
	for (int c = 0; c < cols; ++c) {
		for (int r = 3; r < rows; ++r) {
			char r1 = board[r - 3][c];
			char r2 = board[r - 2][c];
			char r3 = board[r - 1][c];
			char r4 = board[r][c];
			if (r1 == r2 && r2 == r3 && r3 == r4 && r4 == color)
				return EXIT_SUCCESS;
		}
	}

	// Checks pos diagonal
	for (int c = 3; c < cols; ++c) {
		for (int r = 3; r < rows; ++r) {
			char r1 = board[r - 3][c];
			char r2 = board[r - 2][c - 1];
			char r3 = board[r - 1][c - 2];
			char r4 = board[r][c - 3];
			if (r1 == r2 && r2 == r3 && r3 == r4 && r4 == color)
				return EXIT_SUCCESS;
		}
	}

	// Checks neg diagonal
	for (int c = 3; c >= 0; --c) {
		for (int r = 3; r < rows; ++r) {
			char r1 = board[r - 3][c];
			char r2 = board[r - 2][c + 1];
			char r3 = board[r - 1][c + 2];
			char r4 = board[r][c + 3];
			if (r1 == r2 && r2 == r3 && r3 == r4 && r4 == color)
				return EXIT_SUCCESS;
		}
	}

	return EXIT_FAILURE;
}


int test_wins() {
	Environment env = Environment();

	std::cout << "Testing environment win method.\n\n";

	// verticle win test
	env.place_piece('R', 0);
	env.place_piece('R', 0);
	env.place_piece('R', 0);
	env.place_piece('R', 0);
	if (env.has_won('R') == EXIT_SUCCESS)
		std::cout << "Verticle win successful...\n";
	else {
		std::cout << "Verticle win FAILURE.\n";
		return EXIT_FAILURE;
	}

	env = Environment();
	// horizontal win test
	env.place_piece('R', 0);
	env.place_piece('R', 1);
	env.place_piece('R', 2);
	env.place_piece('R', 3);
	if (env.has_won('R') == EXIT_SUCCESS)
		std::cout << "Horizontal win successful...\n";
	else {
		std::cout << "Horizontal win FAILURE.\n";
		return EXIT_FAILURE;
	}

	env = Environment();
	// Diagonal (positive) win test
	env.place_piece('R', 0);
	env.place_piece('B', 1);
	env.place_piece('R', 1);
	env.place_piece('B', 2);
	env.place_piece('B', 2);
	env.place_piece('R', 2);
	env.place_piece('B', 3);
	env.place_piece('B', 3);
	env.place_piece('B', 3);
	env.place_piece('R', 3);
	if (env.has_won('R') == EXIT_SUCCESS)
		std::cout << "Pos diagonal win successful...\n";
	else {
		std::cout << "Pos diagonal win FAILURE.\n";
		return EXIT_FAILURE;
	}

	// Diagonal (positive) win test
	env.place_piece('R', 3);
	env.place_piece('B', 2);
	env.place_piece('R', 2);
	env.place_piece('B', 1);
	env.place_piece('B', 1);
	env.place_piece('R', 1);
	env.place_piece('B', 0);
	env.place_piece('B', 0);
	env.place_piece('B', 0);
	env.place_piece('R', 0);
	if (env.has_won('R') == EXIT_SUCCESS)
		std::cout << "Neg diagonal win successful...\n";
	else {
		std::cout << "Neg diagonal win FAILURE.\n";
		return EXIT_FAILURE;
	}

	std::cout << "All tests successful.\n";
	return EXIT_SUCCESS;
}