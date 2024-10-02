#include "KeyCombinationHandler.h"

bool KeyCombinationHandler::GetCollision(const KeyCombination& comb) {
	if (GetIndexCollision(comb) != -1)
		return true;
	return false;
}


bool KeyCombinationHandler::AddCombination(const std::string& Name, const KeyCombination& comb) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Trying AddCombination\n";
#endif

	if (GetCollision(comb) == true) {
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "Combination not added\n";
#endif
		return false;
	}
	combinations.push_back({ Name,comb });

	KeysToCheck = GetUniqueKeys();
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Combination added\n";

	std::cout << "Unique_Keys: ";
	for (int i = 0; i < KeysToCheck.size(); i++)
	{
		std::cout <<"[" << KeyToStr(KeysToCheck[i].number) << "] ";
	}
	std::cout << "\n";


	std::cout << "Combinations: ";

	std::cout << "|||||||||||||||||||||||||||||||||||||||||\n";
	for (int i = 0; i < combinations.size(); i++){
		std::cout << "------------------------------------\n";
		std::cout << "Name: [" << combinations[i].first << "]\n";
		std::cout << "Keys: ";

		for (int j = 0; j < combinations[i].second.keys.size(); j++)
		{
			std::cout << "<" << KeyToStr(combinations[i].second.keys[j]) << "> ";
		}
		std::cout << "\n";

	}
#endif

	return true;

}


void KeyCombinationHandler::Update() {
	if (flag_StopProcess == false) {
		ProcessAllUniqueKeys();
		ProcessAllFunctions();
	}
}




int KeyCombinationHandler::GetIndexKeyByNumber(const int& number) {
	for (int i = 0; i < KeysToCheck.size(); i++) {
		if (KeysToCheck[i].number == number)
			return i;
	}
	return -1;
}


//TODO: Добавить проверку колво зажатий и нажатий
void KeyCombinationHandler::ProcessAllFunctions() {
	int Value_maxequal = -1;
	int Index_maxequal = -1;

	for (int i = 0; i < combinations.size(); i++) {

		int val = -1;


		bool OnePressed = false;

		for (int j = 0; j < combinations[i].second.keys.size(); j++) {

			int index = GetIndexKeyByNumber(combinations[i].second.keys[j]);

			if (index == -1)
				break;

			if (KeysToCheck[index].isPressed == true) {
				OnePressed = true;
				val++;
			}
			else if (KeysToCheck[index].isDown == true)
				val++;
		}

		if (val + 1 != combinations[i].second.keys.size())
			continue;
		if (OnePressed == false)
			continue;

		if (val > Value_maxequal) {
			Value_maxequal = val;
			Index_maxequal = i;
		}

	}


	for (int i = 0; i < KeysToCheck.size(); i++)
		KeysToCheck[i].isPressed = false;

	if (Index_maxequal == -1)
		return;


#ifdef WITH_DEBUG_OUTPUT
	std::string DebugOutput;
	for (int i = 0; i < combinations[Index_maxequal].second.keys.size(); i++){
		int k = combinations[Index_maxequal].second.keys[i];
		if (i == combinations[Index_maxequal].second.keys.size() - 1)
			DebugOutput += KeyToStr(k);
		else
			DebugOutput += KeyToStr(k) + " + ";
	}

	std::cout << "Function: [" << combinations[Index_maxequal].first << "] <" << DebugOutput << ">\n";
#endif


	combinations[Index_maxequal].second.v_function();




}

void KeyCombinationHandler::ProcessAllUniqueKeys() {

	for (int i = 0; i < KeysToCheck.size(); i++)
	{
		KeysToCheck[i].isDownLastState = KeysToCheck[i].isDown;

		if (glfwGetKey(OpenglWindow::Vars::window, KeysToCheck[i].number) == GLFW_PRESS)
			KeysToCheck[i].isDown = true;
		else
			KeysToCheck[i].isDown = false;

		if (KeysToCheck[i].isDown != KeysToCheck[i].isDownLastState && KeysToCheck[i].isDownLastState == false)
			KeysToCheck[i].isPressed = true;
	}
}



std::vector<Key> KeyCombinationHandler::GetUniqueKeys() {

	std::vector<Key> result;

	auto contains = [&result](int newValue) {
		if (result.empty())
			return false;
		for (int i = 0; i < result.size(); i++) {
			if (newValue == result[i].number)
				return true;
		}
		return false;
		};


	for (int i = 0; i < combinations.size(); i++) {
		for (int j = 0; j < combinations[i].second.keys.size(); j++) {
			const int newKey = combinations[i].second.keys[j];
			if (contains(combinations[i].second.keys[j]) == false)
				result.emplace_back(newKey, false, false);
		}
	}

	std::sort(result.begin(), result.end(), [](Key& a, Key& b) {return a.number > b.number; });

	return result;
}



int KeyCombinationHandler::GetIndexCollision(const KeyCombination& comb) {

	for (int i = 0; i < combinations.size(); i++) {

		if (comb.keys.size() != combinations[i].second.keys.size())
			continue;


		bool AllEqual = true;
		for (int j = 0; j < combinations[i].second.keys.size(); j++) {
			if (combinations[i].second.keys[j] != comb.keys[j]) {
				AllEqual = false;
				break;
			}
		}
		if (AllEqual)
			return i;

	}


	return -1;
}


int KeyCombinationHandler::GetIndexCombinationByName(const std::string& name) {
	for (int i = 0; i < combinations.size(); i++) {
		if (combinations[i].first == name)
			return i;
	}
	return -1;
}
