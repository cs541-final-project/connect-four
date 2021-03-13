#include "environment.h"
#include <iostream>

using namespace std;

int main() {
	Environment env = Environment();
	env.print_board();
	cout << "\n=============\n\n";
	env.print_board();

	test_wins();

	cout << "Press Enter To Exit...";
	cin.get();

	return 0;
}
