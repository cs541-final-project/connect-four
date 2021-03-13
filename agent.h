#pragma once
#ifndef AGENT_H
#define AGENT_H

class Agent {
public:
	Agent(char c);
	~Agent();
	int action(Environment env);
private:
	char color;  // Either 'R' for red, or 'B' for black
};
#endif // !AGENT_H
