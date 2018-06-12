#include <iostream>
#include <ctime>    // for time
#include "Environment.h"
using namespace std;

#TODO: @bhandoko Pending movement in eight directions. Will have to modify the sensing.


int main() {
	
	int id = 1;
	
	int initialPreys = 40;
	int initialHunters = 15;


	Environment myWorld(time(0), id, initialPreys, initialHunters);

	myWorld.display();
	char ch;

	while (cin.get(ch) && ch != 'q') {   // q for quit
		myWorld.simulateOneStep();
		myWorld.display();
	}

	return 0;
}