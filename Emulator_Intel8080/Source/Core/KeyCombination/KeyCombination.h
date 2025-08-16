#ifndef KEY_COMBINATION_H
#define KEY_COMBINATION_H

#include "Config_Compilier.h"
#include "Utils/Keyboard/Keyboard.h"
#include "Utils/Text/Text.h"
#include "Utils/File/File.h"

#include <algorithm>
#include <functional>
#include <string>

struct KeyCombination {
	std::vector<int> keys;
	std::function<void()> v_function;

	std::string KeysStr;
	std::string KeysHumanStr;

	KeyCombination(std::vector<int> keys, std::function<void()> v_function) {
		this->keys = keys;
		this->v_function = v_function;
		sort();
		UpdateStrKey();
	}

	void ChangeKeys(const std::vector<int>& new_keys) {
		keys = new_keys;
		UpdateStrKey();
	}

	std::string GetKeysHumanStr() {
		return KeysHumanStr;
	}

	std::string GetKeysStr() {
		return KeysStr;
	}

	void SetKeysByStr(const std::string& new_keysStr) {
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "Input [" << new_keysStr << "]\n";
#endif
		auto data = Split(new_keysStr, " + ");


		std::vector<int> new_keys_data;
		for (int i = 0; i < data.size(); i++)
		{
			int key = StrToKey(data[i]);
#ifdef WITH_DEBUG_OUTPUT
			std::cout << "<" << data[i] << "> = <" << key << ">\n";
#endif
			if (key == GLFW_KEY_UNKNOWN)
				return;

			new_keys_data.push_back(key);
		}

		keys = new_keys_data;
		UpdateStrKey();
	}


private:

	void sort() {
		std::sort(keys.begin(), keys.end(), std::greater<int>() );
	}


	void UpdateStrKey() {
		KeysStr.clear();
		KeysHumanStr.clear();

		for (int j = 0; j < keys.size(); j++) {
			if (j != keys.size() - 1) {
				KeysHumanStr += KeyToHumanReadbleStr(keys[j]) + " + ";
				KeysStr += KeyToStr(keys[j]) + " + ";
			}
			else {
				KeysHumanStr += KeyToHumanReadbleStr(keys[j]);
				KeysStr += KeyToStr(keys[j]);
			}
		}
	}
};

struct Key {
	int number;
	bool isDown;
	bool isPressed;
	bool isDownLastState = false;

	Key(int number, bool isDown, bool isPressed) {

		this->number = number;
		this->isDown = isDown;
		this->isPressed = isPressed;

		this->isDownLastState = false;
	}
};



#endif // !KEY_COMBINATION_H
