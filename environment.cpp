#include <iostream>
#include "environment.h"
using namespace std;

Environment::Environment() {
	// Initializes board of row x column dimensions to "~" indicating all states are empty.
	rows = MAX_ROWS;
	cols = MAX_COLS;
	open_locations = rows * cols;
	vector<vector<char>> temp_board(rows, vector<char>(cols, '~'));
	board = temp_board;
}

Environment::Environment(const Environment& src) {
	// Copies src
	rows = src.rows;
	cols = src.cols;
	open_locations = rows * cols;
	board = src.board;
}

Environment::~Environment() {
	board.clear();
	//deconstructer
}

// Prints current state of environment to console
int Environment::print_board() {
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			cout << board[r][c] << " ";
		}
		cout << endl;
	}
	return EXIT_SUCCESS;
}

// Returns true if no pieces have been played
int Environment::is_empty() {
	if (num_of_pieces < 1)
		return 1;
	return 0;
}

// Returns true if no remaining locations in board
int Environment::is_full() {
	if (open_locations < 1)
		return 1;
	return 0;
}

// Updates board state with new piece.
// p indicates "color" of piece, c indicates column of placement.
// TODO: Implement penalty upon returning EXIT_FAILURE;
int Environment::place_piece(char p, int c) {
	if (toupper(p) != 'R' && toupper(p) != 'Y') {
		cout << "Invalid placement. Piece does not exist.\n";
		exit(EXIT_FAILURE);
	}

	// Checks if the column is full.
	if (board[0][c] != '~') {
		// std::cout << "Column full.\n";
		return EXIT_FAILURE;
	}

	int r = rows - 1;
	while (board[r][c] != '~' && r > 0)
		r--;

	board[r][c] = p;

	num_of_pieces++;
	open_locations--;

	return EXIT_SUCCESS;
}

// Checks rows of the environment to determine if a color won
// I.E. Has 4 pieces in a row, either vertically, horizontally, or diagonally.
int Environment::has_won(char color) {

	int sum = 0;

	// Checks horizontal
	for (int r = 0; r < rows; ++r) {
		for (int c = 3; c < cols; ++c) {
			char c1 = board[r][c - 3];
			char c2 = board[r][c - 2];
			char c3 = board[r][c - 1];
			char c4 = board[r][c];
			if (c1 == c2 && c2 == c3 && c3 == c4 && c4 == color)
				return 1;
			else {
				if (c1 == c2 && c2 == color)
					sum += 2;
				if (c2 == c3 && c2 == color)
					sum = sum + 4;
			}
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
				return 1;
			else {
				if (r1 == r2 && r2 == color)
					sum += 2;
				if (r2 == r3 && r2 == color)
					sum = sum + 4;
			}
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
				return 1;
			else {
				if (r1 == r2 && r2 == color)
					sum += 2;
				if (r2 == r3 && r2 == color)
					sum = sum + 4;
			}
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
				return 1;
			else {
				if (r1 == r2 && r2 == color)
					sum += 2;
				if (r2 == r3 && r2 == color)
					sum = sum + 4;
			}
		}
	}

	return sum;
}

// Tests has_won() method.
int test_wins() {
	Environment env = Environment();

	cout << "Testing environment win method.\n\n";

	// verticle win test
	env.place_piece('R', 0);
	env.place_piece('R', 0);
	env.place_piece('R', 0);
	env.place_piece('R', 0);
	if (env.has_won('R') == 1)
		cout << "Verticle win successful...\n";
	else {
		cout << "Verticle win FAILURE.\n";
		return EXIT_FAILURE;
	}

	env = Environment();
	// horizontal win test
	env.place_piece('R', 0);
	env.place_piece('R', 1);
	env.place_piece('R', 2);
	env.place_piece('R', 3);
	if (env.has_won('R') == 1)
		cout << "Horizontal win successful...\n";
	else {
		cout << "Horizontal win FAILURE.\n";
		return EXIT_FAILURE;
	}

	env = Environment();
	// Diagonal (positive) win test
	env.place_piece('R', 0);
	env.place_piece('Y', 1);
	env.place_piece('R', 1);
	env.place_piece('Y', 2);
	env.place_piece('Y', 2);
	env.place_piece('R', 2);
	env.place_piece('Y', 3);
	env.place_piece('Y', 3);
	env.place_piece('Y', 3);
	env.place_piece('R', 3);
	if (env.has_won('R') == 1)
		cout << "Pos diagonal win successful...\n";
	else {
		cout << "Pos diagonal win FAILURE.\n";
		return EXIT_FAILURE;
	}

	// Diagonal (positive) win test
	env.place_piece('R', 3);
	env.place_piece('Y', 2);
	env.place_piece('R', 2);
	env.place_piece('Y', 1);
	env.place_piece('Y', 1);
	env.place_piece('R', 1);
	env.place_piece('Y', 0);
	env.place_piece('Y', 0);
	env.place_piece('Y', 0);
	env.place_piece('R', 0);
	if (env.has_won('R') == 1)
		cout << "Neg diagonal win successful...\n";
	else {
		cout << "Neg diagonal win FAILURE.\n";
		return EXIT_FAILURE;
	}

	cout << "All tests successful.\n";
	return 1;
}
