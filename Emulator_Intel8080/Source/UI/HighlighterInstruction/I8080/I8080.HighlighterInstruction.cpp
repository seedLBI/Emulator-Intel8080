#include "I8080.HighlighterInstruction.h"

Singleton_I8080_HighlighterInstruction& Singleton_I8080_HighlighterInstruction::Instance() {
	static Singleton_I8080_HighlighterInstruction obj;
	return obj;
}

Singleton_I8080_HighlighterInstruction::Singleton_I8080_HighlighterInstruction() : Highlighter(u8"Выделитель инструкций Intel8080") {
	InitListWord({
		u8"Перемещение, сохранение и загрузка",
		u8"Операции со стеком",
		u8"Прыжки",
		u8"Вызовы",
		u8"Возвраты",
		u8"Перезагрузки",
		u8"Ввод\\Вывод",
		u8"Инкремент",
		u8"Декремент",
		u8"Сложение",
		u8"Вычитание",
		u8"Логические",
		u8"Повороты",
		u8"Специальные",
		u8"Управление",
		u8"Дерективы транслятора"
		});
	InitListWordsAndColors();
}

Singleton_I8080_HighlighterInstruction::~Singleton_I8080_HighlighterInstruction() {

}

void Singleton_I8080_HighlighterInstruction::InitListWordsAndColors() {

	categories = {
		{
			u8"Перемещение, сохранение и загрузка",
			{u8"mov", u8"mvi", u8"lxi", u8"stax", u8"ldax", u8"sta", u8"lda", u8"shld", u8"lhld", u8"xchg"},
			ImColor{0}
		},
		{
			u8"Операции со стеком",
			{u8"push", u8"pop", u8"xthl", u8"sphl"},
			ImColor{0}
		},
		{
			u8"Прыжки",
			{u8"jmp", u8"jc", u8"jnc", u8"jz", u8"jnz", u8"jp", u8"jm", u8"jpe", u8"jpo", u8"pchl"},
			ImColor{0}
		},
		{
			u8"Вызовы",
			{u8"call", u8"cc", u8"cnc", u8"cz", u8"cnz", u8"cp", u8"cm", u8"cpe", u8"cpo"},
			ImColor{0}
		},
		{
			u8"Возвраты",
			{u8"ret", u8"rc", u8"rnc", u8"rz", u8"rnz", u8"rp", u8"rm", u8"rm", u8"rpe", u8"rpo"},
			ImColor{0}
		},
		{
			u8"Перезагрузки",
			{u8"rst"},
			ImColor{0}
		},
		{
			u8"Ввод\\Вывод",
			{u8"in", u8"out"},
			ImColor{0}
		},
		{
			u8"Инкремент",
			{u8"inr", u8"inx"},
			ImColor{0}
		},
		{
			u8"Декремент",
			{u8"dcr", u8"dcx"},
			ImColor{0}
		},
		{
			u8"Сложение",
			{u8"add", u8"adc", u8"adi", u8"aci", u8"dad"},
			ImColor{0}
		},
		{
			u8"Вычитание",
			{u8"sub", u8"sbb", u8"sui", u8"sbi"},
			ImColor{0}
		},
		{
			u8"Логические",
			{u8"ana", u8"xra", u8"ora", u8"cmp", u8"ani", u8"xri", u8"ori", u8"cpi"},
			ImColor{0}
		},
		{
			u8"Повороты",
			{u8"rlc", u8"rrc", u8"ral", u8"rar"},
			ImColor{0}
		},
		{
			u8"Специальные",
			{u8"cma", u8"stc", u8"cmc", u8"daa"},
			ImColor{0}
		},
		{
			u8"Управление",
			{u8"ei", u8"di", u8"nop", u8"hlt"},
			ImColor{0}
		},
		{
			u8"Дерективы транслятора",
			{u8".const:", u8".set:", u8".adr:"},
			ImColor{0}
		},
	};


}

std::vector<NamedColor> Singleton_I8080_HighlighterInstruction::GetDefaultLightColors() {
	return {
		{ u8"Перемещение, сохранение и загрузка",	ImVec4(1.0 - 0.1, 1.0 - 0.7,1.0 - 0.1, 1.0)},
		{ u8"Операции со стеком",					ImVec4(1.0 - 0.6, 1.0 - 0.3,1.0 - 0.7, 1.0) },
		{ u8"Прыжки",								ImVec4(1.0 - 1.0, 1.0 - 0.1,1.0 - 0.1, 1.0)},
		{ u8"Вызовы",								ImVec4(1.0 - 1.0, 1.0 - 0.1,1.0 - 0.1, 1.0)},
		{ u8"Возвраты",								ImVec4(1.0 - 1.0, 1.0 - 0.1,1.0 - 0.1, 1.0)},
		{ u8"Перезагрузки",							ImVec4(1.0 - 1.0, 1.0 - 0.1,1.0 - 0.1, 1.0)},
		{ u8"Ввод\\Вывод",							ImVec4(1.0 - 0.93,1.0 - 0.5,1.0 - 0.93,1.0)},
		{ u8"Инкремент",							ImVec4(1.0 - 0.0, 1.0 - 0.5,1.0 - 1.0, 1.0)},
		{ u8"Декремент",							ImVec4(1.0 - 0.0, 1.0 - 0.5,1.0 - 1.0, 1.0)},
		{ u8"Сложение",								ImVec4(1.0 - 0.0, 1.0 - 0.5,1.0 - 1.0, 1.0)},
		{ u8"Вычитание",							ImVec4(1.0 - 0.0, 1.0 - 0.5,1.0 - 1.0, 1.0)},
		{ u8"Логические",							ImVec4(1.0 - 1.0, 1.0 - 0.5,1.0 - 0.0, 1.0)},
		{ u8"Повороты",								ImVec4(1.0 - 1.0, 1.0 - 0.5,1.0 - 0.0, 1.0)},
		{ u8"Специальные",							ImVec4(1.0 - 1.0, 1.0 - 0.5,1.0 - 0.0, 1.0)},
		{ u8"Управление",							ImVec4(1.0 - 0.7, 1.0 - 0.4,1.0 - 0.0, 1.0)},
		{ u8"Дерективы транслятора",				ImVec4(0.5,		  0.5,		0.5,	   1.0)}
	};
}
std::vector<NamedColor> Singleton_I8080_HighlighterInstruction::GetDefaultDarkColors() {

	return {
	{ u8"Перемещение, сохранение и загрузка",	ImVec4(0.1,0.7,0.1,1.0)},
	{ u8"Операции со стеком",					ImVec4(0.6,0.3,0.7,1.0) },
	{ u8"Прыжки",								ImVec4(1.0,0.1,0.1,1.0)},
	{ u8"Вызовы",								ImVec4(1.0,0.1,0.1,1.0)},
	{ u8"Возвраты",								ImVec4(1.0,0.1,0.1,1.0)},
	{ u8"Перезагрузки",							ImVec4(1.0,0.1,0.1,1.0)},
	{ u8"Ввод\\Вывод",							ImVec4(0.93,0.5,0.93,1.0)},
	{ u8"Инкремент",							ImVec4(0.0,0.5,1.0,1.0)},
	{ u8"Декремент",							ImVec4(0.0,0.5,1.0,1.0)},
	{ u8"Сложение",								ImVec4(0.0,0.5,1.0,1.0)},
	{ u8"Вычитание",							ImVec4(0.0,0.5,1.0,1.0)},
	{ u8"Логические",							ImVec4(1.0,0.5,0.0,1.0)},
	{ u8"Повороты",								ImVec4(1.0,0.5,0.0,1.0)},
	{ u8"Специальные",							ImVec4(1.0,0.5,0.0,1.0)},
	{ u8"Управление",							ImVec4(0.7,0.4,0.0,1.0)},
	{ u8"Дерективы транслятора",				ImVec4(0.5,0.5,0.5,1.0)}
	};
}

