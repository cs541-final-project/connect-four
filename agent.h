#pragma once
#ifndef AGENT_H
#define AGENT_H
#include "environment.h"


class Agent 
{
public:
	Agent(char c);
	~Agent();
	virtual int action(Environment env);
protected:
	char color;  // Either 'R' for red, or 'B' for black
};

class Miniagent : public Agent {
public:
	Miniagent(char c);
	~Miniagent();
	int action(Environment env);
	int minimax(Environment node, int depth, bool maxPlayer, int alpha, int beta, char c);
private:
};

int evalution_function(Environment env, char color);
std::vector<Environment> available_moves(Environment env, char color);
#endif // !AGENT_H
