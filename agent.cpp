#include "agent.h"

const int MAX = 10000;
const int MIN = -10000;

Agent::Agent(char c) {
	color = c;
}

Agent::~Agent() {
	// placeholder
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

int Miniagent::minimax(Environment node, int depth, bool maxPlayer, int alpha, int beta, char c) {
	if (depth == (node.rows * node.cols) || node.has_won(c))
		return evalution_function(node, c);

	std::vector<Environment> list_of_moves = available_moves(node, c);

	if (maxPlayer)
	{
		int bestVal = MIN;
		for (int i = 0; i < list_of_moves.size(); ++i) {
			int value = minimax(list_of_moves[i], depth + 1, false, alpha, beta, c);
			bestVal = bestVal > value ? bestVal : value;
			alpha = alpha > bestVal ? alpha : bestVal;
			if (beta <= alpha)
				break;
		}
		return bestVal;
	}
	else {
		int bestVal = MAX;
		for (int i = 0; i < list_of_moves.size(); ++i) {
			int value = minimax(list_of_moves[i], depth + 1, true, alpha, beta, c);
			bestVal = bestVal < value ? bestVal : value;
			beta = beta < bestVal ? beta : bestVal;
			if (beta <= alpha)
				break;
		}
		return bestVal;
	}
}

int Miniagent::action(Environment env) {
	return 0;
}

int evalution_function(Environment env, char color) {
	if (env.has_won(color))
		return MAX; // +10000
	return 0;
}

// Returns a vector (list) of available moves at the current position
std::vector<Environment> available_moves(Environment env, char color) {
	std::vector<Environment> moves;

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
