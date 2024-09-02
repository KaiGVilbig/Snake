#pragma once
#include "Coords.h"
#include "Enums.h"

struct Node {
	Coords coords;
	Coords nextCoord;
	Direction direction;
	Direction nextDirection;

	struct Node* next;
};

class Body {
	public:
		Body();
		~Body();
		void addNode(Coords, Coords, Direction, Direction);
		Node* getHead();
		Node* getTail();
		Coords getTailCoords();
		Coords getTailCoordsNext();


	private:
		Node* head;
		Node* tail;
};