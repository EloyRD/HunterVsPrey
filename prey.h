#pragma once

#include <iostream>

#include "Environment.h"
#include "Agent.h"

class Prey : public Agent {
public:
	Prey(Environment* aWorld, int xcoord, int ycoord);

	// In the given world moves this organism.
	void move();

	// Makes this organism breed.
	void breed();

	// Returns the type of this organism.
	AgentType getType() const;

	// The character representation of this organism.
	char representation() const;

	// The size of this organism.
	int size() const;

	bool in_range(int xx, int yy);

private:
	void generateOffspring(int whereX, int whereY);
};
