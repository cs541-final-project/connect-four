#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#define MAX_ROWS 6
#define MAX_COLS 7

#include <vector>

class Environment
{
public:
	Environment();
	~Environment();
	int print_board();
	int place_piece(char p, int c);
	int has_won(char color);
private:
	int rows = 0;
	int cols = 0;
	int num_of_pieces = 0;  // Keeps track of the number of 'pieces' in play
	std::vector<std::vector<char>> board;
};

int test_wins();  // Tests the has_won() method in Environment class.
#endif
