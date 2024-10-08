#include "Utils/Keyboard.Utils.h"

std::string KeyToStr(const int& key) {

	robin_hood::unordered_flat_map<int, std::string> KeyMeans = {
		{GLFW_KEY_0, "0"},{GLFW_KEY_1, "1"},{GLFW_KEY_2,"2"},{GLFW_KEY_3,"3"},{GLFW_KEY_4,"4"},{GLFW_KEY_5,"5"},{GLFW_KEY_6, "6"},{GLFW_KEY_7,"7"},{GLFW_KEY_8,"8"},{GLFW_KEY_9,"9"},
		{GLFW_KEY_SPACE, "Space"},{GLFW_KEY_APOSTROPHE, "Apostrophe"}, {GLFW_KEY_COMMA, "Comma"}, {GLFW_KEY_MINUS,"Minus"}, {GLFW_KEY_PERIOD,"Period"}, {GLFW_KEY_SLASH, "Slash"},
		{GLFW_KEY_SEMICOLON, "Semicolon"},{GLFW_KEY_EQUAL,"Equal"},{GLFW_KEY_A,"A"},{GLFW_KEY_B,"B"},{GLFW_KEY_C,"C"},{GLFW_KEY_D,"D"}, {GLFW_KEY_E,"E"}, {GLFW_KEY_F,"F"},
		{GLFW_KEY_G,"G"},{GLFW_KEY_H,"H"},{GLFW_KEY_I,"I"},{GLFW_KEY_J,"J"},{GLFW_KEY_K,"K"},{GLFW_KEY_L,"L"},{GLFW_KEY_M,"M"},{GLFW_KEY_N,"N"},{GLFW_KEY_O,"O"},{GLFW_KEY_P,"P"},
		{GLFW_KEY_Q,"Q"}, {GLFW_KEY_R,"R"},{GLFW_KEY_S,"S"}, {GLFW_KEY_T,"T"}, {GLFW_KEY_U,"U"}, {GLFW_KEY_V,"V"}, {GLFW_KEY_W,"W"}, {GLFW_KEY_X,"X"}, {GLFW_KEY_Y,"Y"}, {GLFW_KEY_Z,"Z"},
		{GLFW_KEY_LEFT_BRACKET,"LBracket"}, {GLFW_KEY_BACKSLASH,"Backslash"}, {GLFW_KEY_RIGHT_BRACKET,"RBracket"}, {GLFW_KEY_GRAVE_ACCENT,"Grave accent"},
		{GLFW_KEY_ESCAPE,"Esc"}, {GLFW_KEY_ENTER,"Enter"}, {GLFW_KEY_TAB,"TAB"}, {GLFW_KEY_BACKSPACE,"Backspace"}, {GLFW_KEY_INSERT,"Insert"}, {GLFW_KEY_DELETE,"Delete"},
		{GLFW_KEY_RIGHT,"Right"}, {GLFW_KEY_LEFT,"Left"}, {GLFW_KEY_DOWN,"Down"}, {GLFW_KEY_UP,"Up"}, {GLFW_KEY_PAGE_UP,"Page up"}, {GLFW_KEY_PAGE_DOWN, "Page down"},
		{GLFW_KEY_HOME,"Home"}, {GLFW_KEY_END,"End"}, {GLFW_KEY_CAPS_LOCK,"Caps lock"},{GLFW_KEY_PAUSE, "Pause"}, {GLFW_KEY_F1,"F1"}, {GLFW_KEY_F2,"F2"}, {GLFW_KEY_F3,"F3"},
		{GLFW_KEY_F4,"F4"},{GLFW_KEY_F5,"F5"},{GLFW_KEY_F6,"F6"},{GLFW_KEY_F7,"F7"},{GLFW_KEY_F8,"F8"},{GLFW_KEY_F9,"F9"},{GLFW_KEY_F10,"F10"},{GLFW_KEY_F11,"F11"},{GLFW_KEY_F12,"F12"},
		{GLFW_KEY_KP_0, "NUM_0"},{GLFW_KEY_KP_1,"NUM_1"},{GLFW_KEY_KP_2,"NUM_2"},{GLFW_KEY_KP_3,"NUM_3"}, {GLFW_KEY_KP_4,"NUM_4"},{GLFW_KEY_KP_5,"NUM_5"}, {GLFW_KEY_KP_6,"NUM_6"},
		{GLFW_KEY_KP_7, "NUM_7"},{GLFW_KEY_KP_8,"NUM_8"},{GLFW_KEY_KP_9,"NUM_9"}, {GLFW_KEY_KP_DECIMAL,"NUM_DECIMAL"},{GLFW_KEY_KP_DIVIDE,"NUM_DIVIDE"}, {GLFW_KEY_KP_MULTIPLY, "NUM_MULTIPLY"},
		{GLFW_KEY_KP_SUBTRACT,"NUM_SUBTRACT"}, {GLFW_KEY_KP_ADD,"NUM_ADD"}, {GLFW_KEY_KP_ENTER,"NUM_ENTER"}, {GLFW_KEY_KP_EQUAL,"NUM_EQUAL"}, {GLFW_KEY_LEFT_SHIFT,"LShift"},
		{GLFW_KEY_LEFT_CONTROL,"LCtrl"}, {GLFW_KEY_LEFT_ALT,"LAlt"}, {GLFW_KEY_LEFT_SUPER,"L_SUPER"}, {GLFW_KEY_RIGHT_SHIFT,"RShift"}, {GLFW_KEY_RIGHT_CONTROL,"RCtrl"},
		{GLFW_KEY_RIGHT_ALT,"RAlt"}, {GLFW_KEY_RIGHT_SUPER,"R_SUPER"}
	};

	if (KeyMeans.contains(key) == false)
		return "UNSUPPORTED";

	return KeyMeans[key];

}
std::string KeyToHumanReadbleStr(const int& key){
	robin_hood::unordered_flat_map<int, std::string> KeyMeans = {
		{GLFW_KEY_0, "0"},{GLFW_KEY_1, "1"},{GLFW_KEY_2,"2"},{GLFW_KEY_3,"3"},{GLFW_KEY_4,"4"},{GLFW_KEY_5,"5"},{GLFW_KEY_6, "6"},{GLFW_KEY_7,"7"},{GLFW_KEY_8,"8"},{GLFW_KEY_9,"9"},
		{GLFW_KEY_SPACE, "Space"},{GLFW_KEY_APOSTROPHE, "\'"}, {GLFW_KEY_COMMA, ","}, {GLFW_KEY_MINUS,"-"}, {GLFW_KEY_PERIOD,"."}, {GLFW_KEY_SLASH, "/"},
		{GLFW_KEY_SEMICOLON, ";"},{GLFW_KEY_EQUAL,"="},{GLFW_KEY_A,"A"},{GLFW_KEY_B,"B"},{GLFW_KEY_C,"C"},{GLFW_KEY_D,"D"}, {GLFW_KEY_E,"E"}, {GLFW_KEY_F,"F"},
		{GLFW_KEY_G,"G"},{GLFW_KEY_H,"H"},{GLFW_KEY_I,"I"},{GLFW_KEY_J,"J"},{GLFW_KEY_K,"K"},{GLFW_KEY_L,"L"},{GLFW_KEY_M,"M"},{GLFW_KEY_N,"N"},{GLFW_KEY_O,"O"},{GLFW_KEY_P,"P"},
		{GLFW_KEY_Q,"Q"}, {GLFW_KEY_R,"R"},{GLFW_KEY_S,"S"}, {GLFW_KEY_T,"T"}, {GLFW_KEY_U,"U"}, {GLFW_KEY_V,"V"}, {GLFW_KEY_W,"W"}, {GLFW_KEY_X,"X"}, {GLFW_KEY_Y,"Y"}, {GLFW_KEY_Z,"Z"},
		{GLFW_KEY_LEFT_BRACKET,"["}, {GLFW_KEY_BACKSLASH,"\\"}, {GLFW_KEY_RIGHT_BRACKET,"]"}, {GLFW_KEY_GRAVE_ACCENT,"Grave accent"},
		{GLFW_KEY_ESCAPE,"Esc"}, {GLFW_KEY_ENTER,"Enter"}, {GLFW_KEY_TAB,"TAB"}, {GLFW_KEY_BACKSPACE,"Backspace"}, {GLFW_KEY_INSERT,"Insert"}, {GLFW_KEY_DELETE,"Delete"},
		{GLFW_KEY_RIGHT,"Right"}, {GLFW_KEY_LEFT,"Left"}, {GLFW_KEY_DOWN,"Down"}, {GLFW_KEY_UP,"Up"}, {GLFW_KEY_PAGE_UP,"Page up"}, {GLFW_KEY_PAGE_DOWN, "Page down"},
		{GLFW_KEY_HOME,"Home"}, {GLFW_KEY_END,"End"}, {GLFW_KEY_CAPS_LOCK,"Caps lock"},{GLFW_KEY_PAUSE, "Pause"}, {GLFW_KEY_F1,"F1"}, {GLFW_KEY_F2,"F2"}, {GLFW_KEY_F3,"F3"},
		{GLFW_KEY_F4,"F4"},{GLFW_KEY_F5,"F5"},{GLFW_KEY_F6,"F6"},{GLFW_KEY_F7,"F7"},{GLFW_KEY_F8,"F8"},{GLFW_KEY_F9,"F9"},{GLFW_KEY_F10,"F10"},{GLFW_KEY_F11,"F11"},{GLFW_KEY_F12,"F12"},
		{GLFW_KEY_KP_0, "NUM_0"},{GLFW_KEY_KP_1,"NUM_1"},{GLFW_KEY_KP_2,"NUM_2"},{GLFW_KEY_KP_3,"NUM_3"}, {GLFW_KEY_KP_4,"NUM_4"},{GLFW_KEY_KP_5,"NUM_5"}, {GLFW_KEY_KP_6,"NUM_6"},
		{GLFW_KEY_KP_7, "NUM_7"},{GLFW_KEY_KP_8,"NUM_8"},{GLFW_KEY_KP_9,"NUM_9"}, {GLFW_KEY_KP_DECIMAL,"NUM_DECIMAL"},{GLFW_KEY_KP_DIVIDE,"NUM_DIVIDE"}, {GLFW_KEY_KP_MULTIPLY, "NUM_MULTIPLY"},
		{GLFW_KEY_KP_SUBTRACT,"NUM_SUBTRACT"}, {GLFW_KEY_KP_ADD,"NUM_ADD"}, {GLFW_KEY_KP_ENTER,"NUM_ENTER"}, {GLFW_KEY_KP_EQUAL,"NUM_EQUAL"}, {GLFW_KEY_LEFT_SHIFT,"LShift"},
		{GLFW_KEY_LEFT_CONTROL,"LCtrl"}, {GLFW_KEY_LEFT_ALT,"LAlt"}, {GLFW_KEY_LEFT_SUPER,"L_SUPER"}, {GLFW_KEY_RIGHT_SHIFT,"RShift"}, {GLFW_KEY_RIGHT_CONTROL,"RCtrl"},
		{GLFW_KEY_RIGHT_ALT,"RAlt"}, {GLFW_KEY_RIGHT_SUPER,"R_SUPER"}
	};

	if (KeyMeans.contains(key) == false)
		return "UNSUPPORTED";

	return KeyMeans[key];
}



int StrToKey(const std::string& str) {
	robin_hood::unordered_flat_map<std::string,int> StrMeans = {
		{"0",GLFW_KEY_0},{"1",GLFW_KEY_1},{"2",GLFW_KEY_2},{"3",GLFW_KEY_3},{"4",GLFW_KEY_4},{"5",GLFW_KEY_5},{"6",GLFW_KEY_6},{"7",GLFW_KEY_7},{"8",GLFW_KEY_8},{"9",GLFW_KEY_9},
		{"Space",GLFW_KEY_SPACE},{"Apostrophe",GLFW_KEY_APOSTROPHE},{"Comma",GLFW_KEY_COMMA},{"Minus",GLFW_KEY_MINUS},{"Period",GLFW_KEY_PERIOD},{"Slash",GLFW_KEY_SLASH},
		{"Semicolon",GLFW_KEY_SEMICOLON},{"Equal",GLFW_KEY_EQUAL},{"A",GLFW_KEY_A},{"B",GLFW_KEY_B},{"C",GLFW_KEY_C},{"D",GLFW_KEY_D},{"E",GLFW_KEY_E},{"F",GLFW_KEY_F},
		{"G",GLFW_KEY_G},{"H",GLFW_KEY_H},{"I",GLFW_KEY_I},{"J",GLFW_KEY_J},{"K",GLFW_KEY_K},{"L",GLFW_KEY_L},{"M",GLFW_KEY_M},{"N",GLFW_KEY_N},{"O",GLFW_KEY_O},{"P",GLFW_KEY_P},
		{"Q",GLFW_KEY_Q},{"R",GLFW_KEY_R},{"S",GLFW_KEY_S},{"T",GLFW_KEY_T},{"U",GLFW_KEY_U},{"V",GLFW_KEY_V},{"W",GLFW_KEY_W},{"X",GLFW_KEY_X},{"Y",GLFW_KEY_Y},{"Z",GLFW_KEY_Z},
		{"LBracket",GLFW_KEY_LEFT_BRACKET},{"Backslash",GLFW_KEY_BACKSLASH},{"RBracket",GLFW_KEY_RIGHT_BRACKET},{"Grave accent",GLFW_KEY_GRAVE_ACCENT},{"Esc",GLFW_KEY_ESCAPE},{"Enter",GLFW_KEY_ENTER},
		{"TAB",GLFW_KEY_TAB},{"Backspace",GLFW_KEY_BACKSPACE},{"Insert",GLFW_KEY_INSERT},{"Delete",GLFW_KEY_DELETE},{"Right",GLFW_KEY_RIGHT},{"Left",GLFW_KEY_LEFT},{"Down",GLFW_KEY_DOWN},
		{"Up",GLFW_KEY_UP},{"Page up",GLFW_KEY_PAGE_UP},{"Page down",GLFW_KEY_PAGE_DOWN},{"Home",GLFW_KEY_HOME},{"End",GLFW_KEY_END},{"Caps lock",GLFW_KEY_CAPS_LOCK},{ "Pause",GLFW_KEY_PAUSE},
		{"F1",GLFW_KEY_F1},{"F2",GLFW_KEY_F2},{"F3",GLFW_KEY_F3},{"F4",GLFW_KEY_F4},{"F5",GLFW_KEY_F5},{"F6",GLFW_KEY_F6},{"F7",GLFW_KEY_F7},{"F8",GLFW_KEY_F8},{"F9",GLFW_KEY_F9},
		{"F10",GLFW_KEY_F10},{"F11",GLFW_KEY_F11},{"F12",GLFW_KEY_F12},{"NUM_0",GLFW_KEY_KP_0},{"NUM_1",GLFW_KEY_KP_1},{"NUM_2",GLFW_KEY_KP_2},{"NUM_3",GLFW_KEY_KP_3},{"NUM_4",GLFW_KEY_KP_4},
		{"NUM_5",GLFW_KEY_KP_5},{"NUM_6",GLFW_KEY_KP_6},{"NUM_7",GLFW_KEY_KP_7},{"NUM_8",GLFW_KEY_KP_8},{"NUM_9",GLFW_KEY_KP_9},{"NUM_DECIMAL",GLFW_KEY_KP_DECIMAL},
		{"NUM_DIVIDE",GLFW_KEY_KP_DIVIDE},{"NUM_MULTIPLY",GLFW_KEY_KP_MULTIPLY},{"NUM_SUBTRACT",GLFW_KEY_KP_SUBTRACT},{"NUM_ADD",GLFW_KEY_KP_ADD},{"NUM_ENTER",GLFW_KEY_KP_ENTER},
		{"NUM_EQUAL",GLFW_KEY_KP_EQUAL},{"LShift",GLFW_KEY_LEFT_SHIFT},{"LCtrl",GLFW_KEY_LEFT_CONTROL},{"LAlt",GLFW_KEY_LEFT_ALT},{"L_SUPER",GLFW_KEY_LEFT_SUPER},
		{"RShift",GLFW_KEY_RIGHT_SHIFT},{"RCtrl",GLFW_KEY_RIGHT_CONTROL},{"RAlt",GLFW_KEY_RIGHT_ALT},{"R_SUPER",GLFW_KEY_RIGHT_SUPER},
	};

	if (StrMeans.contains(str) == false)
		return GLFW_KEY_UNKNOWN;

	return StrMeans[str];
}


std::vector<int> GetNumberPressedKeys(GLFWwindow *window) {
	std::vector<int> result;
	for (size_t i = 32; i < 96; i++){
		if (glfwGetKey(window,i) == GLFW_PRESS)
			result.emplace_back(i);
	}
	for (size_t i = 256; i < 348; i++){
		if (glfwGetKey(window, i) == GLFW_PRESS)
			result.emplace_back(i);
	}
	return result;
}