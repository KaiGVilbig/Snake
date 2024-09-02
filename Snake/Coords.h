#pragma once
struct Coords {
	int top; 
	int left; 
	int bottom; 
	int right; 

	bool operator==(const Coords& other) const {
		bool equal = false;
		if (top == other.top && left == other.left && bottom == other.bottom && right == other.right) {
			equal = true;
		}
		return equal;
	};
};
