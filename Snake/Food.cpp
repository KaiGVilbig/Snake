#include "Food.h"
#include <cstdlib>

Food::Food(){}

Food::Food(int newTop, int newLeft) {
	coord = { newTop, newLeft, newTop + 10, newLeft + 10 };
	spawned = true;
}

Food::~Food(){}

Coords Food::getCoord() {
	return coord;
}

bool Food::getSpawned() {
	return spawned;
}

int Food::getSize() {
	return size;
}

void Food::newCoords(int newTop, int newLeft) {
	coord = { newTop, newLeft, newTop + 10, newLeft + 10 };
}