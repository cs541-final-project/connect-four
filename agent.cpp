#include "agent.h"
#include "environment.h"

Agent::Agent(char c) {
	color = c;
}

Agent::~Agent() {
	// placeholder
}

int Agent::action(Environment env) {
	// picks a column (denoted col) to place piece in.
	// env.place_piece(color, col);
}