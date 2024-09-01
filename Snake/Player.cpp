#include "Player.h"
#include <cstdlib>

Player::Player() {

}

Player::~Player() {

}

void Player::dealDamage() {
	health -= dmgAmount;
}

void Player::eat() {
	length += 1;
}

void Player::movePlayer(Direction direction) {

	switch (direction) {
		case UP:
			top -= size;
			bottom -= size;
			break;

		case DOWN:
			top += size;
			bottom += size;
			break;

		case LEFT:
			left -= size;
			right -= size;
			break;

		case RIGHT:
			left += size;
			right += size;
			break;
	}
	currDir = direction;
}

bool Player::checkBoundry(int windowWidth, int windowHeight) {
	bool inside = true;

	if (top < 0 || left < 0 || bottom > windowHeight || right > windowWidth) {
		inside = false;
	}

	return inside;
}

Coords Player::getCoords() {
	Coords playerLoc = { top, left, bottom, right };
	return playerLoc;
}

Direction Player::getDirection() {
	return currDir;
}

int Player::getScore() {
	return score;
}

int Player::getHealth() {
	return health;
}

void Player::resetPlayerLoc(int newTop, int newLeft) {
	top = newTop;
	left = newLeft;
	bottom = top + size;
	right = left + size;
	
	currDir = static_cast<Direction>(std::rand() % RIGHT);
}

int Player::getSize() {
	return size;
}