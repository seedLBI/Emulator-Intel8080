#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#include "Config_Compilier.h"
#include "Utils/TextUtils.h"
#include <string>
#include <vector>
#include <iostream>

class SaveSystem
{
public:
	SaveSystem(const std::string& NameObject);
	~SaveSystem();

	virtual std::string Save();
	virtual void Load(const std::string& Data);

	std::string GetName();

protected:
	std::string MakeBegin(const std::string& NameBegin, const int& count_Lines);
	std::string MakeBegin(const int& count_Lines);
	std::string MakeSaveItem(const std::string& NameItem,const std::string& ValueItem);
	std::vector<std::string> SplitLine(const std::string& Line);
	std::vector < std::pair < std::string, std::string >> SplitData(const std::string&Data);

	void PrintDebugInfoAboutData(const std::string& Data);

private:
	std::string NameObject;
};


#endif // !SAVE_SYSTEM_H
