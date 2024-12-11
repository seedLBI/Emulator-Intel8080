#ifndef ITHEME_LOADABLE_H
#define ITHEME_LOADABLE_H

#include <vector>	
#include <string>
#include "UI/Theme/Theme.h"

class IThemeLoadable {
public:
	IThemeLoadable(const std::string& NameObject);
	~IThemeLoadable();


	virtual void LoadColors();
	virtual std::vector<NamedColor> GetDefaultLightColors();
	virtual std::vector<NamedColor> GetDefaultDarkColors();

	void InitListWord(const std::vector<std::string>& Names);
	void LoadColors(const std::vector<NamedColor>& colors);
	void SetDefaultLightColors();
	void SetDefaultDarkColors();


	std::string GetName();
	std::vector<NamedColor> GetColors();
	std::vector<NamedColor>* GetColorsPTR();
protected:
	ObjectColors object_colors;

	void MergeColors(const std::vector<NamedColor>& colors);
};


#endif

