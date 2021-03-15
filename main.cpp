#include "environment.h"
#include "agent.h"
#include <iostream>

using namespace std;

int main() {
	Environment env = Environment();
	env.print_board();
	cout << "\n=============\n\n";
	//env.print_board();

	vector<Environment> temp = available_moves(env, 'B');
	
	for (int i = 0; i < temp.size(); ++i) {
		temp[i].print_board();
		cout << "\n=============\n\n";
	}

	test_wins();

	cout << "Press Enter To Exit...";
	cin.get();

	return 0;
}
