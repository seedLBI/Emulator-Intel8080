#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#include "Utils/Text/Text.h"

#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

class SaveSystem
{
public:
	SaveSystem(const std::string& NameObject);
	~SaveSystem();

	virtual nlohmann::json Save();
	virtual void Load(const nlohmann::json& Data);

	std::string GetName();

	static void merge_json(nlohmann::json& target, const nlohmann::json& source);
	
private:
	std::string NameObject;
};


#endif // !SAVE_SYSTEM_H
