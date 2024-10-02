#ifndef KEY_COMBINATION_H
#define KEY_COMBINATION_H

#include <algorithm>
#include <functional>

struct KeyCombination {
	std::vector<int> keys;
	std::function<void()> v_function;

	KeyCombination(std::vector<int> keys, std::function<void()> v_function) {
		this->keys = keys;
		this->v_function = v_function;

		sort();
	}

private:

	void sort() {
		std::sort(keys.begin(), keys.end(), std::greater<int>() );
	}
};

struct Key {
	int number;
	bool isDown;
	bool isPressed;
	bool isDownLastState = false;
	// Constructor to initialize all members
	Key(int number, bool isDown, bool isPressed) {

		this->number = number;
		this->isDown = isDown;
		this->isPressed = isPressed;

		this->isDownLastState = false;
	}
};



#endif // !KEY_COMBINATION_H
