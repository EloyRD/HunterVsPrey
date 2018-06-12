#include "Hunter.h"
#include "Agent.h"
using namespace std;

Hunter::Hunter(Environment* aWorld, int xcoord, int ycoord) : Agent(aWorld, xcoord, ycoord) {
	death_tik = 0;
}

// In the given world moves this organism.
void Hunter::move() {
	breedTicks++;
	death_tik++;

	if (world->getAt(x, y + 1) != NULL) {
		if (world->getAt(x, y + 1)->getType() == PREY) {
			death_tik = 0;
			delete world->getAt(x, y + 1);
			movesTo(x, y + 1);
			return;
		}
	}

	if (world->getAt(x, y - 1) != NULL) {
		if (world->getAt(x, y - 1)->getType() == PREY) {
			death_tik = 0;
			delete world->getAt(x, y - 1);
			movesTo(x, y - 1);
			return;
		}
	}

	if (world->getAt(x - 1, y) != NULL) {
		if (world->getAt(x - 1, y)->getType() == PREY) {
			death_tik = 0;
			delete world->getAt(x - 1, y);
			movesTo(x - 1, y);
			return;
		}
	}
	if (world->getAt(x + 1, y) != NULL) {
		if (world->getAt(x + 1, y)->getType() == PREY) {
			death_tik = 0;
			delete world->getAt(x + 1, y);
			movesTo(x + 1, y);
			return;
		}
	}

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

void Hunter::generateOffspring(int whereX, int whereY) {
	new Hunter(this->world, whereX, whereY);
	breedTicks = 0;
}

void Hunter::breed() {
	if (breedTicks >= BREED_HUNTER) {
		breedAtAdjacentCell();
	}

}

bool Hunter::isDead() const {
	if (death_tik >= STARVE_HUNTERS) {
		return true;
	}
	else {
		return false;
	}
}

AgentType Hunter::getType() const {
	return HUNTER;
}


char Hunter::representation()const {
	return 'X';
}

int Hunter::size() const {
	return 30;
}

bool Hunter::in_range(int xx, int yy) {
	return (xx >= 0) && (xx < WORLDSIZEX) && (yy >= 0) && (yy < WORLDSIZEY);
}