#include "TextUtils.h"



std::string GetExeFileName() {
    static std::string result;
    if (result.empty()) {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        result = buffer;
    }

    return result;
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


 string int2stringDec(const unsigned char& value) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(1) << std::dec << unsigned int(value);
    string res = ss.str();
    if (res.size() < 3) {
        for (int i = 0; i <= 3 - res.size(); i++)
        {
            res.insert(0, "0");
        }
    }
    return res;
}
 string int2stringBin(const unsigned char& value,const int& countBits) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(1) << std::bitset<8>{value};

    string result = ss.str();

    if (countBits < result.size())
    {
        int c = (result.size() - countBits);

        result.erase(result.begin(), result.begin() + c);
    }

    return result;
}
 string int2stringBin(const unsigned char& value) {
     std::stringstream ss;
     ss << std::setfill('0') << std::setw(1) << std::bitset<8>{value};

     string result = ss.str();

     if (8 < result.size())
     {
         int c = (result.size() - 8);

         result.erase(result.begin(), result.begin() + c);
     }

     return result;
 }
 string int2stringHex(const unsigned char& value) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(1) << std::hex << (value | 0);
    string res = ss.str();
    if (res.size() == 1)
        res.insert(0, "0");
    return res;
}
 string int2string_0x_Hex(const unsigned char& value) {
    return "0x" + int2stringHex(value);
}
 string int2stringDoubleHex(const uint16_t& value) {
    return int2stringHex(value / 256) + int2stringHex(value % 256);
}

 string int2stringDoubleHex(const unsigned char& value1,const unsigned char& value2) {
    return int2stringHex(value1) + int2stringHex(value2);
}
 string int2string_0x_DoubleHex(const unsigned char& value1,const unsigned char& value2) {
    return "0x" + int2stringDoubleHex(value1, value2);
}


 unsigned int string2hex(string value) {
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
 unsigned int Adress_string_2int(string value) {
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

 string cp1251_to_utf8(const char* str) {
    string res;
    int result_u, result_c;
    result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
    if (!result_u) { return 0; }
    wchar_t* ures = new wchar_t[result_u];
    if (!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)) {
        delete[] ures;
        return 0;
    }
    result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
    if (!result_c) {
        delete[] ures;
        return 0;
    }
    char* cres = new char[result_c];
    if (!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)) {
        delete[] cres;
        return 0;
    }
    delete[] ures;
    res.append(cres);
    delete[] cres;
    return res;
}
 std::string utf8_encode(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}
 std::string from_utf8(const std::string& str, const std::locale& loc = std::locale{}) {
    using wcvt = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>;
    auto wstr = wcvt{}.from_bytes(str);
    std::string result(wstr.size(), '0');
    std::use_facet<std::ctype<char32_t>>(loc).narrow(wstr.data(), wstr.data() + wstr.size(), '?', &result[0]);
    return result;
}
 std::string from_utf8(const std::string& str) {
     const std::locale& loc = std::locale{};
     using wcvt = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>;
     auto wstr = wcvt{}.from_bytes(str);
     std::string result(wstr.size(), '0');
     std::use_facet<std::ctype<char32_t>>(loc).narrow(wstr.data(), wstr.data() + wstr.size(), '?', &result[0]);
     return result;
 }
 bool is_valid_utf8(const char* string)
{
    if (!string)
        return true;

    const unsigned char* bytes = (const unsigned char*)string;
    unsigned int cp;
    int num;

    while (*bytes != 0x00)
    {
        if ((*bytes & 0x80) == 0x00)
        {
            // U+0000 to U+007F 
            cp = (*bytes & 0x7F);
            num = 1;
        }
        else if ((*bytes & 0xE0) == 0xC0)
        {
            // U+0080 to U+07FF 
            cp = (*bytes & 0x1F);
            num = 2;
        }
        else if ((*bytes & 0xF0) == 0xE0)
        {
            // U+0800 to U+FFFF 
            cp = (*bytes & 0x0F);
            num = 3;
        }
        else if ((*bytes & 0xF8) == 0xF0)
        {
            // U+10000 to U+10FFFF 
            cp = (*bytes & 0x07);
            num = 4;
        }
        else
            return false;

        bytes += 1;
        for (int i = 1; i < num; ++i)
        {
            if ((*bytes & 0xC0) != 0x80)
                return false;
            cp = (cp << 6) | (*bytes & 0x3F);
            bytes += 1;
        }

        if ((cp > 0x10FFFF) ||
            ((cp >= 0xD800) && (cp <= 0xDFFF)) ||
            ((cp <= 0x007F) && (num != 1)) ||
            ((cp >= 0x0080) && (cp <= 0x07FF) && (num != 2)) ||
            ((cp >= 0x0800) && (cp <= 0xFFFF) && (num != 3)) ||
            ((cp >= 0x10000) && (cp <= 0x1FFFFF) && (num != 4)))
            return false;
    }

    return true;
}

 string GetSymbol_1251_OnNumber(const unsigned char& number_symbol) {
    const vector<string> arr{
        " ",  " ",   " " , u8"©",u8"®",u8"ß",u8"™",u8"ï",  " ", u8"∞",  " ",  " ",  " ",  " ",  " ",  " ",
        " ",  " ",   " " ,   " ",  " ",  " ",  " ",  " ",  " ",   " ",  " ",  " ",  " ",  " ",  " ",  " ",
        " ",  "!",   "\"",   "#",  "$",  "%",  "&",  " ",  "(",   ")",  "*",  "+",  " ",  " ",  " ",  "/",
        "0",  "1",   "2" ,   "3",  "4",  "5",  "6",  "7",  "8",   "9",  ":",  ";",  "<",  "=",  ">",  "?",
        "@",  "A",   "B" ,   "C",  "D",  "E",  "F",  "G",  "H",   "I",  "J",  "K",  "L",  "M",  "N",  "O",
        "P",  "Q",   "R" ,   "S",  "T",  "U",  "V",  "W",  "X",   "Y",  "Z",  "[",  "\\", "]",  "^",  "_",
        "`",  "a",   "b" ,   "c",  "d",  "e",  "f",  "g",  "h",   "i",  "j",  "k",  "l",  "m",  "n",  "o",
        "p",  "q",   "r" ,   "s",  "t",  "u",  "v",  "w",  "x",   "y",  "z",  "{",  "|",  "}",  "~",  " ",
      u8"Ä",u8"Å", u8"Ç" , u8"É",u8"Ñ",u8"Ö",u8"Ü",u8"á",u8"à", u8"â",u8"ä",u8"<",u8"å",u8"ç",u8"é",u8"è",
      u8"ê",u8"'", u8"'" , u8"\"",u8"\"",u8"ï",  "-","-",u8" ", u8"ô",u8"ö",u8">",u8"ú",u8"ù",u8"û",u8"ü",
        " ",u8"°", u8"¢" , u8"é",u8"§",u8"•",u8"¶",u8"ß",u8"®", u8"©",u8"™",u8"´",u8"¨",u8" ",u8"Æ",u8"Ø",
      u8"∞",u8"±", u8"≤" , u8"≥",u8"¥",u8"µ",u8"∂",u8"∑",u8"∏", u8"π",u8"∫",u8"ª",u8"º",u8"Ω",u8"æ",u8"ø",
      u8"¿",u8"¡", u8"¬",  u8"√",u8"ƒ",u8"≈",u8"∆",u8"«",u8"»", u8"…",u8" ",u8"À",u8"Ã",u8"Õ",u8"Œ",u8"œ",
      u8"–",u8"—", u8"“",  u8"”",u8"‘",u8"’",u8"÷",u8"◊",u8"ÿ", u8"Ÿ",u8"⁄",u8"€",u8"‹",u8"›",u8"ﬁ",u8"ﬂ",
      u8"‡",u8"·", u8"‚",  u8"„",u8"‰",u8"Â",u8"Ê",u8"Á",u8"Ë", u8"È",u8"Í",u8"Î",u8"Ï",u8"Ì",u8"Ó",u8"Ô",
      u8"",u8"Ò", u8"Ú",  u8"Û",u8"Ù",u8"ı",u8"ˆ",u8"˜",u8"¯", u8"˘",u8"˙",u8"˚",u8"¸",u8"˝",u8"˛",u8"ˇ"
    };
    return arr[number_symbol];
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
     std::ifstream file(filePath, std::ios::binary);
     if (!file.is_open()) {
         throw std::runtime_error(u8"ÕÂ Û‰‡ÎÓÒ¸ ÓÚÍ˚Ú¸ Ù‡ÈÎ");
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
 void AddSymbolToCount(string& text, char symbol, int count) {
    if (count <= text.size()) {
        return;
    }
    int c = count - text.size();
    for (int i = 0; i < c; ++i) {
        text.insert(text.begin(), symbol);
    }

}
 void SaveUniqueSpaces(string& text) {
    if (text.size() == 0) { return; }

    for (int i = text.size() - 1; i >= 0; --i) {
        if (text[i] == ' ' && text[i] == text[i - 1])
            text.erase(text.begin() + i);
    }
}

void SaveUniqueSpacesWithoutQuotes(string& text) {
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


 void EraseSideSpaces(string& text) {
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


int GetCountSymbol(const string& text, const char& symbol) {
    int result = 0;

    for (char ch : text) {
        if (ch == symbol)
            result++;
    }

    return result;
}

 void DeleteSideSymbols(string& text) {
     if (text.size() < 2)
         return;
     text.erase(text.begin());
     text.erase(text.begin() + text.size() - 1);
 }
 void DeleteAllFromFirstFindSymbol(string& text, const char& symbol) {
    if (text.find_first_of(symbol) != string::npos)
        text.erase(text.begin() + text.find_first_of(symbol), text.end());
}
 void ToLowerAll(string& text) {
    for (int i = 0; i < text.size(); ++i)
        text[i] = tolower(text[i]);
}
 void ToUpperALL(string& text) {
    for (int i = 0; i < text.size(); ++i)
        text[i] = toupper(text[i]);
}
 void EraseAllSymbolType(string& text, const char& symbol) {
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
 void EraseAllSymbolType(vector<string>& text_array, const char& symbol) {
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
 vector<string> split(const string& text_, const string& delimeter_) {
    string s = text_;
    string delimiter = delimeter_;

    vector<string> result;

    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    if (s.length() != 0) {
        result.push_back(s);
    }
    return result;
}
 string cutFloat(string input, const int& countAfterDot) {
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
 vector<string> GetArrayLineFromFile(string path) {
    vector<string> result;
    ifstream ifn;
    ifn.open(path);
    for (string line; getline(ifn, line);) {
        replaceAll(line, "\t", "    ");
        result.push_back(line);
    }
    ifn.close();
    return result;
}
 string OpenFileDialog() {
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
    wstring ws(szFile);
    // your new String
    string str(ws.begin(), ws.end());
    return str;
}

 string SaveFileDialogI8080() {
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
    wstring ws(szFile);
    // your new String
    string str(ws.begin(), ws.end());
    return str;
}
 string SaveFileDialogPNG() {
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
    wstring ws(szFile);
    // your new String
    string str(ws.begin(), ws.end());
    return str;
}
 string SaveFileDialogTXT() {
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
    wstring ws(szFile);
    // your new String
    string str(ws.begin(), ws.end());
    return str;
}