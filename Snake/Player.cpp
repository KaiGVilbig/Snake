#include "Player.h"
#include <cstdlib>

Player::Player(){}

Player::Player(Coords coords) {
	coord = coords;
}

Player::~Player() {

}


Coords Player::getCoords() {
	return coord;
}

Coords Player::getLastCoord() {
	return lastCoord;
}

Direction Player::getDirection() {
	return currDir;
}

Direction Player::getLastDirection() {
	return lastDirection;
}

int Player::getScore() {
	return score;
}

int Player::getHealth() {
	return health;
}

int Player::getSize() {
	return size;
}

int Player::getLength() {
	return length;
}

bool Player::getJustAte() {
	return justAte;
}

void Player::setJustAte(bool ate) {
	justAte = ate;
}


void Player::dealDamage() {
	health -= dmgAmount;
	length = 0;
}

void Player::eat() {
	length += 1;
	score += 1;
	justAte = true;
}

void Player::changeDirection(Direction direction, Node* head) {
	switch (direction) {
		case UP:
			if (currDir != DOWN) {
				currDir = direction;
			}
			break;
		case DOWN:
			if (currDir != UP) {
				currDir = direction;
			}
			break;
		case LEFT:
			if (currDir != RIGHT) {
				currDir = direction;
			}
			break;
		case RIGHT:
			if (currDir != LEFT) {
				currDir = direction;
			}
			break;
	}
}

void Player::movePlayer(Direction direction, Node* head) {

	lastCoord = coord;
	lastDirection = currDir;

	switch (direction) {
		case UP:
			// Prevents jumps when turning
			if (currDir == UP) {
				coord.top -= size;
				coord.bottom -= size;
			}
			break;

		case DOWN:
			// Prevents jumps when turning
			if (currDir == DOWN) {
				coord.top += size;
				coord.bottom += size;
			}
			break;

		case LEFT:
			// Prevents jumps when turning
			if (currDir == LEFT) {
				coord.left -= size;
				coord.right -= size;
			}
			break;

		case RIGHT:
			// Prevents jumps when turning
			if (currDir == RIGHT) {
				coord.left += size;
				coord.right += size;
			}
			break;
	}

	Coords nextCoord = coord;
	Direction nextDirection = currDir;

	while (head != nullptr) {
		head->coords = head->nextCoord;
		head->nextCoord = nextCoord;

		head->direction = head->nextDirection;
		head->nextDirection = nextDirection;

		nextCoord = head->coords;
		nextDirection = head->direction;
		head = head->next;
	}
}

bool Player::checkBoundry(int windowWidth, int windowHeight) {
	bool inside = true;

	if (coord.top < 0 || coord.left < 0 || coord.bottom > windowHeight || coord.right > windowWidth) {
		inside = false;
	}

	return inside;
}

bool Player::checkIntersect(Node* head) {
	bool crashed = false;

	while (head != nullptr) {
		if (coord == head->coords) {
			crashed = true;
			return crashed;
		}
		head = head->next;
	}

	return crashed;
}

void Player::resetPlayerLoc(int newTop, int newLeft) {
	coord = { newTop, newLeft, newTop + size, newLeft + size };
	
	currDir = static_cast<Direction>(std::rand() % RIGHT);
}

bool Player::checkEat(Coords foodCoords) {
	if (coord.left < foodCoords.left && coord.right > foodCoords.right && coord.top < foodCoords.top && coord.bottom > foodCoords.bottom) {
		return true;
	}
	return false;
}