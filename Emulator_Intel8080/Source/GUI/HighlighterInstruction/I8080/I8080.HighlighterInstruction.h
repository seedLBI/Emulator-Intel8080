#ifndef I8080_HIGHLIGHTER_INSTRUCTION_H
#define I8080_HIGHLIGHTER_INSTRUCTION_H

#include "GUI/HighlighterInstruction/Highlighter.h"


class Singleton_I8080_HighlighterInstruction : public Highlighter
{
public:
	static Singleton_I8080_HighlighterInstruction& Instance();


	void InitListWordsAndColors() override;
	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;


private:
	Singleton_I8080_HighlighterInstruction();
	~Singleton_I8080_HighlighterInstruction();

	Singleton_I8080_HighlighterInstruction(Singleton_I8080_HighlighterInstruction const&) = delete;
	Singleton_I8080_HighlighterInstruction& operator= (Singleton_I8080_HighlighterInstruction const&) = delete;
};





#endif // !HIGHLIGHTER_INSTRUCTION_H
