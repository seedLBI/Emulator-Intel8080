#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include "Utils/TextUtils.h"
#include "UI/Theme/interface/IThemeLoadable.h"
#include "robin_hood.h"
#include <vector>
#include <string>


class Highlighter : public IThemeLoadable  {
public:
	Highlighter(const std::string& name);
	~Highlighter();

	ImColor GetColorFromName(std::string name);
	int GetIndexFromName(std::string name);

	ImColor GetColorFromIndex(const int& index);

	void LoadColors() override;

	virtual void InitListWordsAndColors();
	virtual std::vector<NamedColor> GetDefaultLightColors() override;
	virtual std::vector<NamedColor> GetDefaultDarkColors() override;

protected:
	struct ColoredObject {
		std::string Category;
		std::vector<std::string> Names;
		ImColor color;
	};

	std::vector<ColoredObject> categories;
};




#endif // !HIGHLIGHTER_H
