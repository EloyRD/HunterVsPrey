#include <iostream>
#include "Agent.h"
#include "Environment.h"

// Create an organism at the given coordinates in the given world.
Agent::Agent(Environment* aWorld, int xcoord, int ycoord) {
	world = aWorld;
	x = xcoord;
	y = ycoord;
	breedTicks = 0;
	moved = false;
	world->setAt(x, y, this);
}

// flags the organism as moved or not
void Agent::setMoved(bool hasMoved) {
	moved = hasMoved;
}

// has the organism moved or not?
bool Agent::hasMoved() const {
	return moved;
}

// moves the organism from coordinates (x,y) to (xNew,yNew)
void Agent::movesTo(int xNew, int yNew) {

	world->setAt(xNew, yNew, world->getAt(x, y));

	world->setAt(x, y, NULL);

	x = xNew;
	y = yNew;

	world->getAt(x, y)->setMoved(true);
}

// Breeds an organism at an adjacent cell. This method calls the
// generateOffspring() method.
void Agent::breedAtAdjacentCell() {

	if ((world->getAt(x, y + 1) == NULL) && in_range(x, y + 1)) {
		generateOffspring(x, y + 1);
	}
	else if ((world->getAt(x, y - 1) == NULL) && in_range(x, y - 1)) {
		generateOffspring(x, y - 1);
	}
	else if ((world->getAt(x - 1, y) == NULL) && in_range(x - 1, y)) {
		generateOffspring(x - 1, y);
	}
	else if ((world->getAt(x + 1, y) == NULL) && in_range(x + 1, y)) {
		generateOffspring(x + 1, y);
	}
}


bool Agent::in_range(int xx, int yy) {
	return (xx >= 0) && (xx < WORLDSIZEX) && (yy >= 0) && (yy < WORLDSIZEY);
}
// Returns true if organism is dead, false otherwise.
bool Agent::isDead() const {
	return false;
}