#include "environment.h"
#include "agent.h"
#include <iostream>
#include <cstdlib>

const int MAX = 10000;
const int MIN = -10000;

using namespace std;

int main() {
	srand(time(NULL));
	Environment env = Environment();
	Miniagent agent = Miniagent('R');
	Miniagent oppAgent = Miniagent('B');
	env.print_board();
	cout << "\n=============\n\n";
	
	// Minimax agent versus random agent.
	while (!agent.check_win(env) && !oppAgent.check_win(env)) {
		agent.minimax(env, 0, true, MIN, MAX, 'R');
		int index = rand() % 7;
		while (env.place_piece('B', index) == EXIT_FAILURE) {
			index = rand() % 7;
		}
	}

	if (agent.check_win(env))
		cout << "\nRED WINS!\n\n";
	else if (env.has_won('B') == 1)
		cout << "\nBLACK WINS!\n\n";

	env.print_board();

	cout << "Press Enter To Exit...";
	cin.get();

	return 0;
}
