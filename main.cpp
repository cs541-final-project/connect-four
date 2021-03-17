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
	cout << "\nInitial Board\n";
	env.print_board();
	cout << "\n=============\n\n";
	
	cout << "Minimax vs. Random\n";
	// Minimax agent versus random agent.
	while (!agent.check_win(env) && env.has_won('Y') != 1) {
		agent.minimax(env, 0, true, MIN, MAX, 'R');
		int index = rand() % 7;
		while (env.place_piece('Y', index) == EXIT_FAILURE) {
			index = rand() % 7;
		}
	}

	if (agent.check_win(env))
		cout << "\nRED WINS!\n\n";
	else if (env.has_won('Y') == 1)
		cout << "\nYELLOW WINS!\n\n";
	else
		cout << "\nTIE GAME\n\n";

	env.print_board();

	Environment env2 = Environment();
	Miniagent agent2 = Miniagent('R');
	Miniagent oppAgent = Miniagent('Y');

	cout << "\n\n";
	cout << "\nMinimax vs. Minimax\n";
	cout << "\nInitial Board\n";
	env2.print_board();
	cout << "\n=============\n\n";

	// Minimax agent versus other Minimax agent.
	while (!agent2.check_win(env2) && !oppAgent.check_win(env2)) {
		agent2.minimax(env2, 0, true, MIN, MAX, 'R');
		oppAgent.minimax(env2, 0, false, MIN, MAX, 'Y');
	}

	if (agent2.check_win(env2))
		cout << "\nRED WINS!\n\n";
	else if (env2.has_won('Y') == 1)
		cout << "\nYELLOW WINS!\n\n";
	else
		cout << "\nTIE GAME\n\n";
	env2.print_board();

	cout << "\nPress Enter To Exit...";
	cin.get();

	return 0;
}
