#include "environment.h"
#include <iostream>

using namespace std;

int main() {
	Environment env = Environment();
	env.print_board();
	cout << "======\n";
	env.place_piece('R', 0);
	env.print_board();

	cout << "Press Enter To Exit...";
	cin.get();

	return 0;
}