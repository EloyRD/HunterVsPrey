#include <cstdlib>

#include <iostream>
#include "Prey.h"
#include "Agent.h"
#include "Environment.h"
using namespace std;

Prey::Prey(Environment* aWorld, int xcoord, int ycoord) : Agent(aWorld, xcoord, ycoord) {

}

void Prey::move() {
	breedTicks++;
	Move mover = world->randomMove();
	switch (mover) {
	case UP:
		if (world->getAt(x, y + 1) == NULL && in_range(x, y + 1)) {
			movesTo(x, y + 1);
		}
		break;
	case DOWN:
		if (world->getAt(x, y - 1) == NULL && in_range(x, y - 1)) {
			movesTo(x, y - 1);
		}
		break;
	case LEFT:
		if (world->getAt(x - 1, y) == NULL && in_range(x - 1, y)) {
			movesTo(x - 1, y);
		}
		break;
	case RIGHT:
		if (world->getAt(x + 1, y) == NULL && in_range(x + 1, y)) {
			movesTo(x + 1, y);
		}
		break;
	default:
		break;
	}
}

void Prey::breed() {
	if (breedTicks >= BREED_PREYS) {
		breedAtAdjacentCell();
	}
}


void Prey::generateOffspring(int whereX, int whereY) {
	new Prey(this->world, whereX, whereY);
	breedTicks = 0;
}


AgentType Prey::getType() const {
	return PREY;
}

char Prey::representation() const {
	return 'o';
}

int Prey::size() const {
	return 10;
}

bool Prey::in_range(int xx, int yy) {
	return (xx >= 0) && (xx < WORLDSIZEX) && (yy >= 0) && (yy < WORLDSIZEY);
}