#include "agent.h"

const int MAX = 10000;
const int MIN = -10000;

Agent::Agent(char c) {
	color = c;
}

Agent::~Agent() {
	//deconstructer
}

int Agent::action(Environment env) {
	// picks a column (denoted col) to place piece in.
	// env.place_piece(color, col);
	return 0;
}

Miniagent::Miniagent(char c) : Agent(c) {
	// placeholder
}

Miniagent::~Miniagent() {
	// placeholder
}

bool Miniagent::check_win(Environment env) {
	if (env.has_won(color) == 1) {
		return true;
	}
	return false;
}

int Miniagent::minimax(Environment &node, int depth, bool maxPlayer, int alpha, int beta, char c) {
	char oppColor = ' ';
	if (c == 'R')
		oppColor = 'Y';
	else if (c == 'Y')
		oppColor = 'R';
	else {
		std::cout << "Invalid player piece.\n";
		exit(EXIT_FAILURE);
	}

	if (depth == DEPTH || node.has_won(c) == 1|| node.is_full())
		return evalution_function(node, c);

	vector<Environment> list_of_moves = available_moves(node, c);

	int move_index = 0;

	if (maxPlayer)
	{
		int bestVal = MIN;
		for (unsigned long int i = 0; i < list_of_moves.size(); ++i) {
			int value = minimax(list_of_moves[i], depth + 1, false, alpha, beta, oppColor);
			bestVal = bestVal > value ? bestVal : value;
			move_index = bestVal > value ? move_index : i;
			alpha = alpha > bestVal ? alpha : bestVal;
			if (beta <= alpha)
				break;
		}
		node = list_of_moves[move_index];
		return bestVal;
	}
	else {
		int bestVal = MAX;
		for (unsigned long int i = 0; i < list_of_moves.size(); ++i) {
			int value = minimax(list_of_moves[i], depth + 1, true, alpha, beta, oppColor);
			bestVal = bestVal < value ? bestVal : value;
			move_index = bestVal < value ? move_index : i;
			beta = beta < bestVal ? beta : bestVal;
			if (beta <= alpha)
				break;
		}
		node = list_of_moves[move_index];
		return bestVal;
	}
}

int Miniagent::action(Environment &env) {
	int value = 0;
	int move_index = 0;
	vector<Environment> list_of_moves = available_moves(env, color);

	for (unsigned long int i = 0; i < list_of_moves.size(); ++i) {
		int temp_value = minimax(list_of_moves[i], 0, true, 0, 0, color);
		move_index = temp_value > value ? i : move_index;
		value = temp_value > value ? temp_value : value;
	}

	env = list_of_moves[move_index];

	return EXIT_SUCCESS;
}

int evalution_function(Environment env, char color) {
	char oppColor = ' ';
	if (color == 'R')
		oppColor = 'Y';
	else if (color == 'Y')
		oppColor = 'R';
	else {
		std::cout << "Invalid player piece.\n";
		exit(EXIT_FAILURE);
	}

	int score = env.has_won(color);
	int opScore = env.has_won(oppColor);

	if (score == EXIT_SUCCESS)
		return MAX; // +10000
	if (opScore == EXIT_SUCCESS)
		return MIN; // -10000

	// returns total score accounting for all pieces on board. Returns negative score if opponent has 'higher' score.
	return score > opScore ? score : -opScore;
}

// Returns a vector (list) of available moves at the current position
vector<Environment> available_moves(Environment env, char color) {
	vector<Environment> moves;

	for (int c = 0; c < env.cols; ++c) {
		for (int r = 0; r < env.rows; ++r) {
			if ((env.board[r][c] != 'E' && r > 0) || r == env.rows - 1) {
				// make copy of env
				Environment m1 = Environment(env);
				// place piece at location
				m1.place_piece(color, c);
				// add to moves list
				moves.push_back(m1);
				break;
			}
		}
	}
	return moves;
}
