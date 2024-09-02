#include "Food.h"
#include <cstdlib>

Food::Food(){}

Food::Food(int newTop, int newLeft) {
	coord = { newTop, newLeft, newTop + 10, newLeft + 10 };
	model = static_cast<Models>(std::rand() % (FOOD_PUMPKIN - FOOD_BANANA + 1) + FOOD_BANANA);
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

Models Food::getModel() {
	return model;
}

void Food::newCoords(int newTop, int newLeft, Models newModel) {
	coord = { newTop, newLeft, newTop + 10, newLeft + 10 };
	model = newModel;
}