#pragma once

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include "robin_hood.h"
#include <map>
#include <regex>
#include "algorithm"

#include <iostream>
#include "UI/Setting/ISettingObject.h"
#include "UI/Theme/interface/IThemeLoadable.h"
#include "UI/HighlighterInstruction/I8080/I8080.HighlighterInstruction.h"
#include "SaveSystem/SaveSystem.h"
#include "OpenglWindow/OpenglWindow.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "IconFontCppHeaders/IconsFontAwesome6.h"
#include "Emulator/Processors/Intel8080/InfoInstruction/InfoInstruction.Display.h"
#include "Utils/ImGui.Utils.h"
#include "Utils/TextUtils.h"
#include "Utils/UTF8.h"


class TextEditor : public ISettingObject, public IThemeLoadable
{
private:

	enum InstructionArguments {
		Register8,
		Register16_WithSP,
		Register16_WithPSW,
		Register16_OnlyBD,
		Value8,
		Value16,
		ValueSpecial,
		ArgumentsCount
	};
	enum InstructionBytes {
		Opcode,
		Value,
		Value_low,
		Value_high,
		Adress_low,
		Adress_high,
		MAX
	};
	enum InstructionFlagsState {
		Unaffected,
		Affected,
		Reset,
		Set
	};
	enum InstructionTicksMean {
		Condition,
		M_Used,
		Always
	};

	struct FlagsList {
		InstructionFlagsState Sign;
		InstructionFlagsState Zero;
		InstructionFlagsState ACarry;
		InstructionFlagsState Parity;
		InstructionFlagsState Carry;

	};


	struct CommandArguments {
		std::string type_argument;
		std::vector<std::string> available_values;
	};

	class ArgumentsArray {
	public:
		ArgumentsArray() {
			Arguments.resize(InstructionArguments::ArgumentsCount);

			Arguments[InstructionArguments::Register8] = 
				CommandArguments{ u8"Рег.8",{"A","B","C","D","E","H","L","M"}};
			Arguments[InstructionArguments::Register16_WithSP] =
				CommandArguments{ u8"Рег.16",{"B","D","H","SP"} };
			Arguments[InstructionArguments::Register16_WithPSW] =
				CommandArguments{ u8"Рег.16",{"B","D","H","PSW"} };
			Arguments[InstructionArguments::Register16_OnlyBD] =
				CommandArguments{ u8"Рег.16",{"B","D"} };
			Arguments[InstructionArguments::Value8] =
				CommandArguments{ u8"Число.8",{"0-255","0x00-0xff"} };
			Arguments[InstructionArguments::Value16] =
				CommandArguments{ u8"Число.16",{"0-65535","0x0000-0xffff"} };
			Arguments[InstructionArguments::ValueSpecial] =
				CommandArguments{ u8"Число.Спец",{"0-8","0x00-0x08"} };
		}

		CommandArguments GetArgument(int number_argument) {
			return Arguments[number_argument];
		}

	private:
		std::vector<CommandArguments> Arguments;
	};
	class OpcodesArray {
	public:
		OpcodesArray() {
			arr.resize(InstructionBytes::MAX);
			arr[Opcode] = u8"Опкод";
			arr[Value] = u8"Число";
			arr[Value_low] = u8"Число.Млад.";
			arr[Value_high] = u8"Число.Стар.";
			arr[Adress_low] = u8"Адрес.Млад.";
			arr[Adress_high] = u8"Адрес.Стар.";
		}

		std::string GetOpcodeName(int number_opcode) {
			return arr[number_opcode];
		}
	private:
		std::vector<std::string> arr;
	};

	const std::vector<std::string> info_flagsStatus = {
		u8"Не изменяется",
		u8"Изменяется",
		u8"Устанавливается 0",
		u8"Устанавливается 1",
	};

	std::string Get_info_ticks_mean(std::vector<int> ticks, InstructionTicksMean mean) {
		if (mean == InstructionTicksMean::Condition)
			return std::to_string(ticks[0]) + u8" - Выполняется условие.\n" + std::to_string(ticks[1]) + u8" - Иначе.";
		else if (mean == InstructionTicksMean::M_Used)
			return std::to_string(ticks[0]) + u8" - Используется регистр M.\n" + std::to_string(ticks[1]) + u8" - Иначе.";
		else if (mean == InstructionTicksMean::Always)
			return std::to_string(ticks[0]) + u8" - Всегда.";
	}


	ArgumentsArray info_arguments;
	OpcodesArray info_opcode;

public:
	enum class PaletteIndex {
		Default,
		Keyword,
		Number,
		String,
		CharLiteral,
		Punctuation,
		Preprocessor,
		Identifier,
		KnownIdentifier,
		PreprocIdentifier,
		Comment,
		MultiLineComment,
		Background,
		Cursor,
		Selection,
		ErrorMarker,
		Breakpoint,
		LineNumber,
		CurrentLineFill,
		CurrentLineFillInactive,
		CurrentLineEdge,
		Command_Translator,
		Instruction,
		Finder_NotFind,
		Max,
	};

	enum class SelectionMode
	{
		Normal,
		Word,
		Line
	};

	struct Breakpoint
	{
		int mLine;
		bool mEnabled;
		std::string mCondition;

		Breakpoint()
			: mLine(-1)
			, mEnabled(false)
		{}
	};

	// Represents a character coordinate from the user's point of view,
	// i. e. consider an uniform grid (assuming fixed-width font) on the
	// screen as it is rendered, and each cell has its own coordinate, starting from 0.
	// Tabs are counted as [1..mTabSize] count empty spaces, depending on
	// how many space is necessary to reach the next tab stop.
	// For example, coordinate (1, 5) represents the character 'B' in a line "\tABC", when mTabSize = 4,
	// because it is rendered as "    ABC" on the screen.
	struct Coordinates
	{
		int mLine, mColumn;
		Coordinates() : mLine(0), mColumn(0) {}
		Coordinates(int aLine, int aColumn) : mLine(aLine), mColumn(aColumn)
		{
			assert(aLine >= 0);
			assert(aColumn >= 0);
		}
		static Coordinates Invalid() { static Coordinates invalid(-1, -1); return invalid; }

		bool operator ==(const Coordinates& o) const
		{
			return
				mLine == o.mLine &&
				mColumn == o.mColumn;
		}

		bool operator !=(const Coordinates& o) const
		{
			return
				mLine != o.mLine ||
				mColumn != o.mColumn;
		}

		bool operator <(const Coordinates& o) const
		{
			if (mLine != o.mLine)
				return mLine < o.mLine;
			return mColumn < o.mColumn;
		}

		bool operator >(const Coordinates& o) const
		{
			if (mLine != o.mLine)
				return mLine > o.mLine;
			return mColumn > o.mColumn;
		}

		bool operator <=(const Coordinates& o) const
		{
			if (mLine != o.mLine)
				return mLine < o.mLine;
			return mColumn <= o.mColumn;
		}

		bool operator >=(const Coordinates& o) const
		{
			if (mLine != o.mLine)
				return mLine > o.mLine;
			return mColumn >= o.mColumn;
		}
	};

	struct Identifier {
		Coordinates mLocation;
	};

	typedef std::string String;
	typedef std::unordered_map<std::string, Identifier> Identifiers;
	typedef std::unordered_set<std::string> Keywords;
	typedef std::map<int, std::string> ErrorMarkers;
	typedef std::unordered_set<int> Breakpoints;
	typedef std::array<ImU32, (unsigned)PaletteIndex::Max> Palette;
	typedef uint8_t Char;

	struct Glyph
	{
		Char mChar;
		PaletteIndex mColorIndex = PaletteIndex::Default;
		int mColorCustomIndex = -1;
		bool mComment : 1;
		bool mMultiLineComment : 1;
		bool mPreprocessor : 1;

		Glyph(Char aChar, PaletteIndex aColorIndex) : mChar(aChar), mColorIndex(aColorIndex),
			mComment(false), mMultiLineComment(false), mPreprocessor(false) {}
	};

	typedef std::vector<Glyph> Line;
	typedef std::vector<Line> Lines;

	struct LanguageDefinition
	{
		typedef std::pair<std::string, PaletteIndex> TokenRegexString;
		typedef std::vector<TokenRegexString> TokenRegexStrings;
		typedef bool(*TokenizeCallback)(const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end, PaletteIndex & paletteIndex);

		std::string mName;
		Keywords mKeywords;
		Identifiers mIdentifiers;
		Identifiers mPreprocIdentifiers;
		std::string mCommentStart, mCommentEnd, mSingleLineComment;
		char mPreprocChar;
		bool mAutoIndentation;

		TokenizeCallback mTokenize;

		TokenRegexStrings mTokenRegexStrings;

		bool mCaseSensitive;

		LanguageDefinition()
			: mPreprocChar('#'), mAutoIndentation(true), mTokenize(nullptr), mCaseSensitive(true)
		{
		}

		static const LanguageDefinition& I8080();
	};

	TextEditor();
	~TextEditor();

	void SetLanguageDefinition(const LanguageDefinition& aLanguageDef);
	const LanguageDefinition& GetLanguageDefinition() const { return mLanguageDefinition; }

	const Palette& GetPalette() const { return mPaletteBase; }
	void SetPalette(const Palette& aValue);

	void DeleteAllErrorMarkers();


	void DeleteAllBreakpoints();
	void AddBreakPoint(const int& indexLine);
	std::vector<int> GetBreakpoints();


	void SetErrorMarkers(const ErrorMarkers& aMarkers) { mErrorMarkers = aMarkers; }
	void SetBreakpoints(const Breakpoints& aMarkers) { mBreakpoints = aMarkers; }


	void Render(const char* aTitle, const ImVec2& aSize = ImVec2(), bool aBorder = false);
	void SetText(const std::string& aText);
	std::string GetText() const;

	void SetTextLines(const std::vector<std::string>& aLines);
	std::vector<std::string> GetTextLines() const;

	std::string GetSelectedText() const;
	std::string GetCurrentLineText()const;

	int GetTotalLines() const { return (int)mLines.size(); }
	bool IsOverwrite() const { return mOverwrite; }

	void SetReadOnly(bool aValue);
	bool IsReadOnly() const { return mReadOnly; }
	bool IsTextChanged() const { return mTextChanged; }
	void SetTextNotChanged() { mTextChanged = false;}

	bool IsCursorPositionChanged() const { return mCursorPositionChanged; }

	bool IsColorizerEnabled() const { return mColorizerEnabled; }
	void SetColorizerEnable(bool aValue);

	Coordinates GetCursorPosition() const { return GetActualCursorCoordinates(); }
	void SetCursorPosition(const Coordinates& aPosition);

	inline void SetHandleMouseInputs    (bool aValue){ mHandleMouseInputs    = aValue;}
	inline bool IsHandleMouseInputsEnabled() const { return mHandleKeyboardInputs; }

	inline void SetHandleKeyboardInputs (bool aValue){ mHandleKeyboardInputs = aValue;}
	inline bool IsHandleKeyboardInputsEnabled() const { return mHandleKeyboardInputs; }

	inline void SetImGuiChildIgnored    (bool aValue){ mIgnoreImGuiChild     = aValue;}
	inline bool IsImGuiChildIgnored() const { return mIgnoreImGuiChild; }

	inline void SetShowWhitespaces(bool aValue) { mShowWhitespaces = aValue; }
	inline bool IsShowingWhitespaces() const { return mShowWhitespaces; }

	void SetTabSize(int aValue);
	inline int GetTabSize() const { return mTabSize; }

	void InsertText(const std::string& aValue);
	void InsertText(const char* aValue);

	void MoveUp(int aAmount = 1, bool aSelect = false);
	void MoveDown(int aAmount = 1, bool aSelect = false);
	void MoveLeft(int aAmount = 1, bool aSelect = false, bool aWordMode = false);
	void MoveRight(int aAmount = 1, bool aSelect = false, bool aWordMode = false);
	void MoveTop(bool aSelect = false);
	void MoveBottom(bool aSelect = false);
	void MoveHome(bool aSelect = false);
	void MoveEnd(bool aSelect = false);

	void MoveLineUp(bool aSelect = false);
	void MoveLineDown(bool aSelect = false);


	void SetSelectionStart(const Coordinates& aPosition);
	void SetSelectionEnd(const Coordinates& aPosition);
	void SetSelection(const Coordinates& aStart, const Coordinates& aEnd, SelectionMode aMode = SelectionMode::Normal);
	void SelectWordUnderCursor();
	void SelectAll();
	bool HasSelection() const;

	void Copy();
	void Cut();
	void Paste();
	void Delete();

	bool CanUndo() const;
	bool CanRedo() const;
	void Undo(int aSteps = 1);
	void Redo(int aSteps = 1);

	static const Palette& GetDarkPalette();
	static const Palette& GetLightPalette();
	static const Palette& GetRetroBluePalette();


	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;
	void LoadColors() override;


	void DrawSetting() override;
	std::string SaveSetting() override;
	void LoadSetting(const std::string& Data) override;

	bool Flag_EnableAutoTab = true;
	bool Flag_AnalyzeLineForInstruction = true;

private:
	typedef std::vector<std::pair<std::regex, PaletteIndex>> RegexList;

	struct EditorState
	{
		Coordinates mSelectionStart;
		Coordinates mSelectionEnd;
		Coordinates mCursorPosition;
	};

	class UndoRecord
	{
	public:
		UndoRecord() {}
		~UndoRecord() {}

		UndoRecord(
			const std::string& aAdded,
			const TextEditor::Coordinates aAddedStart,
			const TextEditor::Coordinates aAddedEnd,

			const std::string& aRemoved,
			const TextEditor::Coordinates aRemovedStart,
			const TextEditor::Coordinates aRemovedEnd,

			TextEditor::EditorState& aBefore,
			TextEditor::EditorState& aAfter);

		void Undo(TextEditor* aEditor);
		void Redo(TextEditor* aEditor);

		std::string mAdded;
		Coordinates mAddedStart;
		Coordinates mAddedEnd;

		std::string mRemoved;
		Coordinates mRemovedStart;
		Coordinates mRemovedEnd;

		EditorState mBefore;
		EditorState mAfter;
	};

	typedef std::vector<UndoRecord> UndoBuffer;

	void ProcessInputs();
	void Colorize(int aFromLine = 0, int aCount = -1);
	void ColorizeRange(int aFromLine = 0, int aToLine = 0);
	void ColorizeInternal();
	float TextDistanceToLineStart(const Coordinates& aFrom) const;
	void EnsureCursorVisible();
	int GetPageSize() const;
	std::string GetText(const Coordinates& aStart, const Coordinates& aEnd) const;
	Coordinates GetActualCursorCoordinates() const;
	Coordinates SanitizeCoordinates(const Coordinates& aValue) const;
	void Advance(Coordinates& aCoordinates) const;
	void DeleteRange(const Coordinates& aStart, const Coordinates& aEnd);
	int InsertTextAt(Coordinates& aWhere, const char* aValue);
	void AddUndo(UndoRecord& aValue);
	Coordinates ScreenPosToCoordinates(const ImVec2& aPosition) const;
	Coordinates FindWordStart(const Coordinates& aFrom) const;
	Coordinates FindWordEnd(const Coordinates& aFrom) const;
	Coordinates FindNextWord(const Coordinates& aFrom) const;
	int GetCharacterIndex(const Coordinates& aCoordinates) const;
	int GetCharacterColumn(int aLine, int aIndex) const;
	int GetLineCharacterCount(int aLine) const;
	int GetLineMaxColumn(int aLine) const;
	bool IsOnWordBoundary(const Coordinates& aAt) const;
	void RemoveLine(int aStart, int aEnd);
	void RemoveLine(int aIndex);
	Line& InsertLine(int aIndex);
	void EnterCharacter(ImWchar aChar, bool aShift);
	void Backspace();
	void DeleteSelection();
	std::string GetWordUnderCursor() const;
	std::string GetWordAt(const Coordinates& aCoords) const;
	std::string GetTextAfterTextUnderCursor(const Coordinates& aCoords) const;


	ImU32 GetGlyphColor(const Glyph& aGlyph) const;

	void HandleKeyboardInputs();
	void HandleMouseInputs_Step1();
	void HandleMouseInputs_Step2();

	void HandleMouseInputs_Step2Again();
	bool SetAgain_Step2 = false;
	float SetAgain_LineNo = 0;

	bool mCopyingWithoutSelection = false;


	void Render();

	void Draw_FindWindow();
	void Toggle_OpenFindWindow();
	bool mWindowFind = false;
	bool mWindowFind_Launched = false;
	int CountLines_In_Window = 0;

	bool FindFlag_Register = false;
	bool FindFlag_AllWord = false;


	struct FindedWord {
		Coordinates WordStart;
		Coordinates WordEnd;

		Coordinates Find_Start;
		Coordinates Find_End;

		float Attention_Time = 0.f;
	};
	
	struct DataFinder {

		std::string WordSetted;

		std::vector<FindedWord> FindedWords;
		int index_current = -1;

		void Next() {
			if (FindedWords.empty())
				return;

			index_current++;
			if (index_current > FindedWords.size() - 1)
				index_current = 0;

			FindedWords[index_current].Attention_Time = TimeAttention_Default;
		}
		void Prev() {
			if (FindedWords.empty())
				return;

			index_current--;
			if (index_current < 0)
				index_current = FindedWords.size() - 1;

			FindedWords[index_current].Attention_Time = TimeAttention_Default;
		}


		void Update() {
			for (int i = 0; i < FindedWords.size(); i++){
				FindedWords[i].Attention_Time -= OpenglWindow::GetDeltaTime();
				if (FindedWords[i].Attention_Time < 0)
					FindedWords[i].Attention_Time = 0.f;
			}
		}


		void Find(const std::vector<std::string>& lines_text, const std::string& word, const bool& Flag_Register,const bool& Flag_CompleteWord,const bool& AnywayRecalculate) {

			if (word.empty()) {
				WordSetted.clear();
				index_current = -1;
				FindedWords.clear();
				return;
			}

			if (word == WordSetted && !AnywayRecalculate) {
				Next();
				return;
			}

			std::vector<std::vector<std::string>> utf8Line_text(lines_text.size());

			UTF8_SPLITER_ERROR error;
			std::vector<std::string> utf8_word = utf8_splitter(word, error);;

			if (!Flag_Register)
				Lowercase_UTF8_Text(utf8_word);




			if (!Flag_Register) {
				for (int i = 0; i < lines_text.size(); i++) {
					utf8Line_text[i] = utf8_splitter(lines_text[i], error);
					Lowercase_UTF8_Text(utf8Line_text[i]);
				}
			}
			else {
				for (int i = 0; i < lines_text.size(); i++)
					utf8Line_text[i] = utf8_splitter(lines_text[i], error);
			}


			index_current = -1;
			FindedWords.clear();
			WordSetted = word;

			for (int i = 0; i < utf8Line_text.size(); i++) {

				int addedCollumn = 0;
				int len = 0;

				for (int j = 0; j < utf8Line_text[i].size(); j++) {

					if (utf8Line_text[i][j] == "\t")
						len += 4 - (len % 4);
					else
						len++;

					if (utf8Line_text[i][j] == utf8_word[0]) {

						int index_line = i;
						int index_column = j;

						bool AllCorrect = true;

						bool BeginLine = j == 0;

						for (int k = 1; k < utf8_word.size(); k++) {
							j++;
							len++;
							if (j > utf8Line_text[i].size() - 1) {
								AllCorrect = false;
								break;
							}

							if (utf8_word[k] != utf8Line_text[i][j]) {
								AllCorrect = false;
								break;
							}
						}

						if (AllCorrect) {



							bool WordLeftSpace = false;
							bool WordRightSpace = false;


							if (index_column == 0)
								WordLeftSpace = true;
							else
								WordLeftSpace = utf8Line_text[i][index_column - 1] == " " || utf8Line_text[i][index_column - 1] == "\t";

							if (j == utf8Line_text[i].size() - 1)
								WordRightSpace = true;
							else
								WordRightSpace = utf8Line_text[i][j + 1] == " " || utf8Line_text[i][j+1] == "\t";


							if (Flag_CompleteWord && (!WordLeftSpace || !WordRightSpace)) {
								continue;
							}


							if (index_current == -1) {
								index_current = 0;
							}

							FindedWord pos_word;

							pos_word.Find_Start = Coordinates(index_line, len - utf8_word.size());
							pos_word.Find_End = Coordinates(index_line, len);


							FindedWords.push_back(pos_word);

							//Coordinates coord_equals_begin(index_line, index_column);


						}



					}



				}
			}
		}


		const float TimeAttention_Default = 0.3f;
	};


	DataFinder _DataFinder;


	void SetCursorAtCoord_ChoosedWord() {
		if (_DataFinder.FindedWords.empty())
			return;


		ImGuiWindow* window = ImGui::GetCurrentWindow();
		float PrevScale = window->FontWindowScale;

		ImGui::SetWindowFontScale(mVirtualFontSize);

		const float fontSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize() * mVirtualFontSize, FLT_MAX, -1.0f, "#", nullptr, nullptr).x;
		ImVec2 mCharAdvance = ImVec2(fontSize, ImGui::GetTextLineHeightWithSpacing() * mLineSpacing);

		float lineee = _DataFinder.FindedWords[_DataFinder.index_current].Find_Start.mLine - CountLines_In_Window / 2;

		if (lineee < 0)
			lineee = 0;

		ImGui::SetScrollY(mCharAdvance.y * lineee);

		ImGui::SetWindowFontScale(PrevScale);
	}



	float mLineSpacing;
	Lines mLines;
	EditorState mState;
	UndoBuffer mUndoBuffer;
	int mUndoIndex;


	float mVirtualFontSize;

	int mTabSize;
	bool mOverwrite;
	bool mReadOnly;
	bool mWithinRender;
	bool mScrollToCursor;
	bool mScrollToTop;
	bool mTextChanged;
	bool mColorizerEnabled;
	float mTextStart;                   // position (in pixels) where a code line starts relative to the left of the TextEditor.
	int  mLeftMargin;
	bool mCursorPositionChanged;
	int mColorRangeMin, mColorRangeMax;
	SelectionMode mSelectionMode;
	bool mHandleKeyboardInputs;
	bool mHandleMouseInputs;
	bool mIgnoreImGuiChild;
	bool mShowWhitespaces;

	Palette mPaletteBase;
	Palette mPalette;
	LanguageDefinition mLanguageDefinition;
	RegexList mRegexList;


	bool mCheckComments;
	Breakpoints mBreakpoints;
	ErrorMarkers mErrorMarkers;
	ImVec2 mCharAdvance;
	Coordinates mInteractiveStart, mInteractiveEnd;
	std::string mLineBuffer;
	uint64_t mStartTime;

	float mLastClick;
};
