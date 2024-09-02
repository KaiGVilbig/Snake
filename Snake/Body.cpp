#include "Body.h"

Body::Body() {
	head = nullptr;
	tail = nullptr;
}

Body::~Body() {
	Node* curr = head;

	while (curr != nullptr) {
		Node* nextNode = curr->next;
		delete curr;
		curr = nextNode;
	}

	head = nullptr;
	tail = nullptr;
}

void Body::addNode(Coords curr, Coords next, Direction direct, Direction nextDir) {
	Node* temp = new Node;
	temp->coords = curr;
	temp->nextCoord = next;
	temp->next = nullptr;
	temp->direction = direct;
	temp->nextDirection = nextDir;
	temp->prev = tail;

	if (head == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		tail = temp;
	}
}

Node* Body::getHead() {
	return head;
}

Node* Body::getTail() {
	return tail;
}

Coords Body::getTailCoords() {
	return tail->coords;
}

Coords Body::getTailCoordsNext() {
	return tail->nextCoord;
}
