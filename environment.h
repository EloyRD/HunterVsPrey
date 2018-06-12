#pragma once

#include "Agent.h"
#include "Parameters.h"

// The possible moves
enum Move { UP = 0, DOWN, LEFT, RIGHT };

struct Position
{
	int x;
	int y;
};

class Environment
{
public:
	// Constructor: creates and initializes this world. the seed is used for
	// seeding the random behaviour.
	Environment(unsigned int seed, int _id, int _initialPopulationPreys, int _initialPopulationHunmters);
	int timeStep;
	

	// Destructor.
	~Environment();

	// Returns the organism at the given coordinates.
	Agent* getAt(int x, int y) const;

	// Sets the organism org at position (x,y).
	void setAt(int x, int y, Agent* org);

	// Displays this world.
	void display() const;

	// Simulates one time step in this world.
	void simulateOneStep();

	// Returns a random position in the grid.
	Position randomPosition() const;

	// Returns a random move (UP, DOWN, LEFT or RIGHT).
	Move randomMove() const;

private:
	// The grid in which the organisms live. According the to image below,
	// the correct iteration order through grid starts at the top left
	// corner (i.e. grid[0][0]), loops through one column at a time and ends
	// at the bottom right corner (i.e. grid[WORLDSIZE-1][WORLDSIZE-1]).
	//
	// grid[0, 0]          , grid[1, 0],      ...,      grid[WORLDSIZE-1, 0]
	// grid[0, 1]          , grid[1, 1],      ...,      grid[WORLDSIZE-1, 1]
	//    .                                                     .
	//    .                                                     .
	//    .                                                     .
	// grid[0, WORLDSIZE-2], grid[1, WORLDSIZE-2], ..., grid[WORLDSIZE-1, WORLDSIZE-2]
	// grid[0, WORLDSIZE-1], grid[1, WORLDSIZE-1], ..., grid[WORLDSIZE-1, WORLDSIZE-1]
	//
	// (See e.g. the destructor for correct iteration through the grid)
	Agent* grid[WORLDSIZEX][WORLDSIZEY];

	// Randomly create `count` many organisms of type `orgType`.  This
	// method uses the parameterized constructor in Prey and Hunter.
	void createOrganisms(AgentType orgType, int count);

	// Reset all organisms to not moved. This is necessary because later we
	// iterate through the grid starting from the top left moving to the
	// bottom right looking for an organism to move. Say if an organism
	// moves down, we don't want to move the organism again when we reach
	// it.
	void resetOrganisms();

	// Make every organisms in this world of type aType move. Make sure to
	// to iterate through grid in order as specified above and only move an
	// organism if it hasn't moved already.
	void moveOrganism(AgentType aType);

	// Remove all dead organism from this world. Iterates through the grid
	// and uses the method Organism::isDead() to test if an organism is
	// dead.
	void cleanup();

	// Make every organism in this world breed. Make sure to iterate
	// through grid in order as specified above and to only breed organisms
	// that have moved, since breeding places new organisms on the map we
	// don't want to try and breed those.
	void breedOrganisms();

	// Identifier for the world
	int id;

	// Initial population of preys
	int initialPopulationPreys;

	// Initial Population of Hunters
	int initialPopulationHunters;
};