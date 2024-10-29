#include "TextUtils.h"


std::string ConvertCP1251ToUTF8(const std::string& str)
{
    int len = MultiByteToWideChar(1251, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(1251, 0, str.c_str(), -1, wstr, len);

    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, 0, 0);
    char* utf8 = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, 0, 0);

    std::string result(utf8);
    delete[] wstr;
    delete[] utf8;

    return result;
}

std::string GetExeFileName() {
    static std::string result;
    if (result.empty()) {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        result = buffer;
    }
    return ConvertCP1251ToUTF8(result);
}

 std::string GetExePath()
{
     static std::string f;
     if (f.empty()) {
          f = GetExeFileName();
         f = f.substr(0, f.find_last_of("\\/"));
     }
     return f;
}


 std::string int2stringDec(const unsigned char& value) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(1) << std::dec << unsigned int(value);
    std::string res = ss.str();
    if (res.size() < 3) {
        for (int i = 0; i <= 3 - res.size(); i++)
        {
            res.insert(0, "0");
        }
    }
    return res;
}
 std::string int2stringBin(const unsigned char& value,const int& countBits) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(1) << std::bitset<8>{value};

    std::string result = ss.str();

    if (countBits < result.size())
    {
        int c = (result.size() - countBits);

        result.erase(result.begin(), result.begin() + c);
    }

    return result;
}
 std::string int2stringBin(const unsigned char& value) {
     std::stringstream ss;
     ss << std::setfill('0') << std::setw(1) << std::bitset<8>{value};

     std::string result = ss.str();

     if (8 < result.size())
     {
         int c = (result.size() - 8);

         result.erase(result.begin(), result.begin() + c);
     }

     return result;
 }
 std::string int2stringHex(const unsigned char& value) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(1) << std::hex << (value | 0);
    std::string res = ss.str();
    if (res.size() == 1)
        res.insert(0, "0");
    return res;
}
 std::string int2string_0x_Hex(const unsigned char& value) {
    return "0x" + int2stringHex(value);
}
 std::string int2stringDoubleHex(const uint16_t& value) {
    return int2stringHex(value / 256) + int2stringHex(value % 256);
}

 std::string int2stringDoubleHex(const unsigned char& value1,const unsigned char& value2) {
    return int2stringHex(value1) + int2stringHex(value2);
}
 std::string int2string_0x_DoubleHex(const unsigned char& value1,const unsigned char& value2) {
    return "0x" + int2stringDoubleHex(value1, value2);
}


 unsigned int string2hex(std::string value) {
    long n;
    if (value.substr(0, 2) == "0x") {

        value.erase(value.begin(), value.begin() + 2);
        char* p;
        n = strtol(value.c_str(), &p, 16);
    }
    else if (value.substr(0, 2) == "0b") {
        value.erase(value.begin(), value.begin() + 2);
        char* p;
        n = strtol(value.c_str(), &p, 2);
    }
    else {
        n = stoi(value);
    }

    return n;
}
 unsigned int Adress_string_2int(std::string value) {
    if (value.substr(0, 2) == "0x")
        return string2hex(value);
    else
        return stoi(value);
}


 std::vector<std::string> GetArguments(int argc, char* argv[]) {
    std::string current_exec_name = argv[0]; // Name of the current exec program
    std::vector<std::string> all_args;

    if (argc > 1) {
        all_args.assign(argv + 1, argv + argc);
    }
    return all_args;
}

 std::string GetSymbol_1251_OnNumber(const unsigned char& number_symbol) {
    const static std::vector<std::string> arr{
        u8" ",  u8" ",   u8" " , u8" ",u8" ",u8" ",u8" ",u8" ",  u8" ", u8"\\t",  u8"\\n",  u8" ",  u8" ",  u8" ",  u8" ",  u8" ",
        u8" ",  u8" ",  u8" " ,   u8" ",  u8" ",  u8" ",  u8" ",  u8" ",  u8" ",   u8" ",  u8" ",  u8" ",  u8" ",  u8" ",  u8" ",  u8" ",
        u8" ",  u8"!",   u8"\"",   u8"#",  u8"$",  u8"%",  u8"&",  u8" ",  u8"(",   u8")",  u8"*",  u8"+", u8" ",  u8" ",  u8" ",  u8"/",
        u8"0",  u8"1",   u8"2" ,   u8"3",  u8"4",  u8"5",  u8"6",  u8"7",  u8"8",   u8"9",  u8":",  u8";",  u8"<",  u8"=",  u8">",  u8"?",
        u8"@",  u8"A",   u8"B" ,   u8"C",  u8"D",  u8"E",  u8"F",  u8"G",  u8"H",   u8"I",  u8"J",  u8"K",  u8"L", u8"M",  u8"N",  u8"O",
        u8"P",  u8"Q",   u8"R" ,   u8"S",  u8"T",  u8"U",  u8"V",  u8"W",  u8"X",   u8"Y",  u8"Z",  u8"[",  u8"\\", u8"]",  u8"^",  u8"_",
        u8"`",  u8"a",   u8"b" ,   u8"c",  u8"d",  u8"e",  u8"f",  u8"g",  u8"h",   u8"i",  u8"j",  u8"k",  u8"l",  u8"m",  u8"n",  u8"o",
        u8"p",  u8"q",   u8"r" ,   u8"s",  u8"t",  u8"u",  u8"v",  u8"w",  u8"x",   u8"y",  u8"z",  u8"{",  u8"|",  u8"}",  u8"~",  u8" ",
      u8"Ä",u8"Å", u8"Ç" , u8"É",u8"Ñ",u8"Ö",u8"Ü",u8"á",u8"à", u8"â",u8"ä",u8"<",u8"å",u8"ç",u8"é",u8"è",
      u8"ê",u8"'", u8"'" , u8"\"",u8"\"",u8"ï",  u8"-",u8"-",u8" ", u8"ô",u8"ö",u8">",u8"ú",u8"ù",u8"û",u8"ü",
      u8" ",u8"°", u8"¢" , u8"é",u8"§",u8"•",u8"¶",u8"ß",u8"®", u8"©",u8"™",u8"´",u8"¨",u8" ",u8"Æ",u8"Ø",
      u8"∞",u8"±", u8"≤" , u8"≥",u8"¥",u8"µ",u8"∂",u8"∑",u8"∏", u8"π",u8"∫",u8"ª",u8"º",u8"Ω",u8"æ",u8"ø",
      u8"¿",u8"¡", u8"¬",  u8"√",u8"ƒ",u8"≈",u8"∆",u8"«",u8"»", u8"…",u8" ",u8"À",u8"Ã",u8"Õ",u8"Œ",u8"œ",
      u8"–",u8"—", u8"“",  u8"”",u8"‘",u8"’",u8"÷",u8"◊",u8"ÿ", u8"Ÿ",u8"⁄",u8"€",u8"‹",u8"›",u8"ﬁ",u8"ﬂ",
      u8"‡",u8"·", u8"‚",  u8"„",u8"‰",u8"Â",u8"Ê",u8"Á",u8"Ë", u8"È",u8"Í",u8"Î",u8"Ï",u8"Ì",u8"Ó",u8"Ô",
      u8"",u8"Ò", u8"Ú",  u8"Û",u8"Ù",u8"ı",u8"ˆ",u8"˜",u8"¯", u8"˘",u8"˙",u8"˚",u8"¸",u8"˝",u8"˛",u8"ˇ"
    };

    return arr[number_symbol];;
}


 int GetCountLines(const std::string& Text) {
     if (Text.size() == 0)
         return 0;

     int count = 0;
     size_t it = 0;
     while (1) {
         it = Text.find('\n', it + 1);
         if (it == std::string::npos) {
             break;
         }
         count++;
     }

     return count;
 }



 std::vector<uint8_t> readFileToByteArray(const std::string& filePath) {
     std::ifstream file(stringUTF8_to_wstring(filePath), std::ios::binary);
     if (!file.is_open()) {
         return {};
     }

     file.seekg(0, std::ios::end);
     std::streamsize fileSize = file.tellg();
     file.seekg(0, std::ios::beg);

     std::vector<uint8_t> byteArray(fileSize);

     if (!file.read(reinterpret_cast<char*>(byteArray.data()), fileSize)) {
         throw std::runtime_error(u8"Œ¯Ë·Í‡ ÔË ˜ÚÂÌËË Ù‡ÈÎ‡");
     }
     file.close();
     return byteArray;
 }


//TODO:
 void AddSymbolToCount(std::string& text, char symbol, int count) {
    if (count <= text.size()) {
        return;
    }
    int c = count - text.size();
    for (int i = 0; i < c; ++i) {
        text.insert(text.begin(), symbol);
    }

}

 void AddSymbolInEndToCount(std::string& text,const char& symbol,const int& count) {
     if (count <= text.size()) {
         return;
     }
     int c = count - text.size();
     for (int i = 0; i < c; ++i) {
         text.push_back(symbol);
     }

 }
 void SaveUniqueSpaces(std::string& text) {
    if (text.size() == 0) { return; }

    for (int i = text.size() - 1; i >= 0; --i) {
        if (text[i] == ' ' && text[i] == text[i - 1])
            text.erase(text.begin() + i);
    }
}

void SaveUniqueSpacesWithoutQuotes(std::string& text) {
     if (text.size() == 0) { return; }

     bool QuoteOpen = false;
     for (int i = text.size() - 1; i >= 0; --i) {
         if (text[i] == '\'' || text[i] == '\"') {
             if (i - 1 >= 0){
                 if (text[i-1] != '\\')
                     QuoteOpen = !QuoteOpen;
             }
             else
                 QuoteOpen = !QuoteOpen;

         }
         if (text[i] == ' ' && text[i] == text[i - 1] && QuoteOpen == false)
             text.erase(text.begin() + i);
     }
}


 void EraseSideSpaces(std::string& text) {
    for (int i = 0; i < text.size() - 1; ++i) {
        if (text[i] == ' ') {
            text.erase(text.begin() + i);
            i--;
        }
        else
            break;
    }

    for (int i = text.size() - 1; i >= 0; --i) {
        if (text[i] == ' ')
            text.erase(text.begin() + i);
        else
            break;
    }
}


int GetCountSymbol(const std::string& text, const char& symbol) {
    int result = 0;

    for (char ch : text) {
        if (ch == symbol)
            result++;
    }

    return result;
}

 void DeleteSideSymbols(std::string& text) {
     if (text.size() < 2)
         return;
     text.erase(text.begin());
     text.erase(text.begin() + text.size() - 1);
 }
 void DeleteAllFromFirstFindSymbol(std::string& text, const char& symbol) {
    if (text.find_first_of(symbol) != std::string::npos)
        text.erase(text.begin() + text.find_first_of(symbol), text.end());
}
 void ToLowerAll(std::string& text) {
    for (int i = 0; i < text.size(); ++i)
        text[i] = tolower(text[i]);
}
 void ToUpperALL(std::string& text) {
    for (int i = 0; i < text.size(); ++i)
        text[i] = toupper(text[i]);
}
 void EraseAllSymbolType(std::string& text, const char& symbol) {
    for (int i = 0; i < text.size(); ++i)
    {
        if (text[i] == symbol)
        {
            if (i != 0 && text[i - 1] == '\\')
            {
                text.erase(text.begin() + i - 1);
                i--;
            }
            else {
                text.erase(text.begin() + i);
                i--;
            }

        }
    }
}
 void EraseAllSymbolType(std::vector<std::string>& text_array, const char& symbol) {
    for (int i = 0; i < text_array.size(); ++i)
    {
        EraseAllSymbolType(text_array[i], symbol);
    }

}
 void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}
 std::vector<std::string> split(const std::string & text_, const std::string & delimeter_) {
    std::string s = text_;
    std::string delimiter = delimeter_;

    std::vector<std::string> result;

    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    if (s.length() != 0) {
        result.push_back(s);
    }
    return result;
}
 std::string cutFloat(std::string input, const int& countAfterDot) {
    int pos = input.find('.');
    if (pos + 1 + countAfterDot > input.size() - 1)
        return input;
    else {
        input.erase(input.begin() + pos + 1 + countAfterDot, input.end());

        for (int i = input.size() - 1; i >= 0; i--)
        {
            if (input[i] == '0')
                input.erase(input.begin() + i);
            else 
                break;
        }

        if (input.back() == '.')
            input.erase(input.begin() + input.size() - 1);

        return input;
    }
}
 std::vector<std::string> GetArrayLineFromFile(std::string path) {
    std::vector<std::string> result;
    std::ifstream ifn;
    ifn.open(path);
    for (std::string line; getline(ifn, line);) {
        replaceAll(line, "\t", "    ");
        result.push_back(line);
    }
    ifn.close();
    return result;
}

 std::string OpenFileDialog() {
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[460]{};        // buffer for file name
    HWND hwnd = GetConsoleWindow();              // owner window
    HANDLE hf;              // file handle
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"I8080 files\0*.I8080\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    // Display the Open dialog box. 

    if (GetOpenFileName(&ofn) == TRUE) {
        //hf = CreateFile(ofn.lpstrFile,
        //    GENERIC_READ,
        //    0,
        //    (LPSECURITY_ATTRIBUTES)NULL,
        //    OPEN_EXISTING,
        //    FILE_ATTRIBUTE_NORMAL,
        //    (HANDLE)NULL);

    }
    std::wstring ws(szFile);
    // your new String
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

    return myconv.to_bytes(ws);
}
 std::string OpenRomFileDialog() {
     OPENFILENAME ofn;       // common dialog box structure
     wchar_t szFile[460]{};        // buffer for file name
     HWND hwnd = GetConsoleWindow();              // owner window
     HANDLE hf;              // file handle
     // Initialize OPENFILENAME
     ZeroMemory(&ofn, sizeof(ofn));
     ofn.lStructSize = sizeof(ofn);
     ofn.hwndOwner = hwnd;
     ofn.lpstrFile = szFile;
     // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
     // use the contents of szFile to initialize itself.
     ofn.lpstrFile[0] = '\0';
     ofn.nMaxFile = sizeof(szFile);
     ofn.lpstrFilter = L"Binary files\0*.rom\0";
     ofn.nFilterIndex = 1;
     ofn.lpstrFileTitle = NULL;
     ofn.nMaxFileTitle = 0;
     ofn.lpstrInitialDir = NULL;
     ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
     // Display the Open dialog box. 

     if (GetOpenFileName(&ofn) == TRUE) {
         //hf = CreateFile(ofn.lpstrFile,
         //    GENERIC_READ,
         //    0,
         //    (LPSECURITY_ATTRIBUTES)NULL,
         //    OPEN_EXISTING,
         //    FILE_ATTRIBUTE_NORMAL,
         //    (HANDLE)NULL);

     }
     std::wstring ws(szFile);
     // your new String
     std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

     return myconv.to_bytes(ws);
 }

 std::string SaveFileDialogI8080() {
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[460]{};        // buffer for file name
    HWND hwnd = GetConsoleWindow();              // owner window
    HANDLE hf;              // file handle
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"I8080 files\0*.I8080\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    // Display the Open dialog box. 

    if (GetSaveFileName(&ofn) == TRUE) {

    }
    std::wstring ws(szFile);
    // your new String
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

    return myconv.to_bytes(ws);
}
 std::string SaveFileDialogPNG() {
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[460]{};        // buffer for file name
    HWND hwnd = GetConsoleWindow();              // owner window
    HANDLE hf;              // file handle
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Png\0*.png\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    // Display the Open dialog box. 

    if (GetSaveFileName(&ofn) == TRUE) {

    }
    std::wstring ws(szFile);
    // your new String
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

    return myconv.to_bytes(ws);
}
 std::string SaveFileDialogTXT() {
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[460]{};        // buffer for file name
    HWND hwnd = GetConsoleWindow();              // owner window
    HANDLE hf;              // file handle
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Txt\0*.txt\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    // Display the Open dialog box. 

    if (GetSaveFileName(&ofn) == TRUE) {

    }
    std::wstring ws(szFile);
    // your new String

    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

    return myconv.to_bytes(ws);
}


 std::wstring stringUTF8_to_wstring(const std::string& str)
 {
     std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
     return myconv.from_bytes(str);
 }
 std::string wstring_to_stringUTF8(const std::wstring& str)
 {
     std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
     return myconv.to_bytes(str);
 }
