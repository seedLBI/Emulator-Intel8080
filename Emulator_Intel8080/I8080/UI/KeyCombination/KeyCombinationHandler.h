#ifndef KEY_COMBINATION_HANDLER_H
#define KEY_COMBINATION_HANDLER_H

#include "Config_Compilier.h"
#include "OpenglWindow/OpenglWindow.h"
#include "KeyCombination.h"
#include "Utils/Keyboard.Utils.h"
#include <functional>




class KeyCombinationHandler
{
public:
	KeyCombinationHandler() = default;
	~KeyCombinationHandler() = default;
	
	
	bool GetCollision(const KeyCombination& comb);

	bool AddCombination(const std::string& Name, const KeyCombination& comb);

	void Update();

	


private:

	std::vector<std::pair<std::string, KeyCombination>> combinations;
	int GetIndexCombinationByName(const std::string& name);
	int GetIndexCollision(const KeyCombination& comb);


	std::vector<Key> KeysToCheck;
	int GetIndexKeyByNumber(const int& number);
	std::vector<Key> GetUniqueKeys();


	bool flag_StopProcess = false;
	void ProcessAllFunctions();
	void ProcessAllUniqueKeys();

};




#endif