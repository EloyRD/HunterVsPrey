#include <iostream>
#include <cstdlib>  // for rand

#include "Environment.h"
#include "Prey.h"
#include "Hunter.h"
using namespace std;

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
Environment::Environment(unsigned int seed, int _id, int _initialPopulationPreys, int _initialPopulationHunters) {
	// seed the random generator
	srand(seed);
	// Create an empty world
	id = _id;

	initialPopulationPreys = _initialPopulationPreys;
	initialPopulationHunters = _initialPopulationHunters;

	for (int i = 0; i < WORLDSIZEX; i++) {
		for (int j = 0; j < WORLDSIZEY; j++) {
			grid[i][j] = NULL;
		}
	}
	timeStep = 0;
	// creates the preys = 3
	createOrganisms(PREY, initialPopulationPreys);
	// creates the hunters = 8
	createOrganisms(HUNTER, initialPopulationHunters);
}

// Deallocate memory allocated to organisms in this world.
Environment::~Environment() {
	for (int i = 0; i < WORLDSIZEX; i++) {
		for (int j = 0; j < WORLDSIZEY; j++) {
			if (grid[i][j] != NULL) {
				delete grid[i][j];
			}
		}
	}
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Agent* Environment::getAt(int x, int y) const {
	if ((x >= 0) && (x < WORLDSIZEX) && (y >= 0) && (y < WORLDSIZEY)) {
		return grid[x][y];
	}
	else {
		return NULL;
	}
}

// Sets the entry at x,y to the value passed in.
void Environment::setAt(int x, int y, Agent* org) {
	if ((x >= 0) && (x < WORLDSIZEX) && (y >= 0) && (y < WORLDSIZEY)) {
		grid[x][y] = org;
	}
}

// Displays the world in ASCII.
void Environment::display() const {
	int numPreys = 0;
	int numHunters = 0;

	cout << endl << endl;
	for (int j = 0; j < WORLDSIZEY; j++) {
		for (int i = 0; i < WORLDSIZEX; i++) {
			if (grid[i][j] == NULL) {
				cout << "_";
			}
			else {
				if (grid[i][j]->getType() == PREY) {
					numPreys++;
				}
				else if (grid[i][j]->getType() == HUNTER) {
					numHunters++;
				}
				cout << grid[i][j]->representation();
			}
		}
		cout << endl;
	}
	cout << "Preys 'o': " << numPreys << " Hunters 'X': " << numHunters << endl;
	cout << "Timestep:" << timeStep << " World ID:" << id << endl;
}

void Environment::simulateOneStep() {
	// The main routine that simulates one turn in the world:
	// 1. move hunters
	// 2. move preys
	// 3. make hunters starve (which happends under a certain condition)
	// 4. make the organisms breed (again which happens under a certain
	// condition).

	// Reset all organisms to not moved
	resetOrganisms();

	// Move the hunters
	moveOrganism(HUNTER);

	// Move the preys
	moveOrganism(PREY);

	// Make the hunters starve
	cleanup();

	//Make them breed
	breedOrganisms();

	timeStep++;
}

Position Environment::randomPosition() const {    // returns a random number in the range 0 to MAX-1
	Position p;
	p.x = rand() % WORLDSIZEX;
	p.y = rand() % WORLDSIZEY;
	return p;
}


Move Environment::randomMove() const {
	return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

void Environment::createOrganisms(AgentType orgType, int count) {
	int orgCount = 0;
	while (orgCount < count) {
		Position p = randomPosition();

		// Only put prey in empty spot
		if (grid[p.x][p.y] == NULL) {
			orgCount++;
			if (orgType == PREY) {
				new Prey(this, p.x, p.y);   // Create a Prey and put it into the world
			}
			else if (orgType == HUNTER) {
				new Hunter(this, p.x, p.y);   // Create a Hunter and put it into the world
			}
		}
	}
}

// Reset all organisms to not moved
void Environment::resetOrganisms() {
	for (int i = 0; i < WORLDSIZEX; i++) 	{
		for (int j = 0; j < WORLDSIZEY; j++) 		{
			if (grid[i][j] != NULL) 			{
				grid[i][j]->setMoved(false);
			}
		}
	}
}

// Move all organisms of type aType
void Environment::moveOrganism(AgentType aType) {
	for (int i = 0; i < WORLDSIZEX; i++) 	{
		for (int j = 0; j < WORLDSIZEY; j++) 		{
			if (grid[i][j] != NULL) 			{
				if (grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved())) 				{
					grid[i][j]->move();
				}
			}
		}
	}
}

// Remove all dead organisms from this world.
void Environment::cleanup() {
	for (int i = 0; i < WORLDSIZEX; i++) {
		for (int j = 0; j < WORLDSIZEY; j++) {
			// Kill off any organisms that haven't eaten recently
			if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
				delete grid[i][j];
				grid[i][j] = NULL;
			}
		}
	}
}

// Make the organisms breed
void Environment::breedOrganisms() {
	for (int i = 0; i < WORLDSIZEX; i++) 	{
		for (int j = 0; j < WORLDSIZEY; j++) 		{
			if (grid[i][j] != NULL) 			{
				grid[i][j]->breed();
			}
		}
	}
}