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

    std::string value = arr[number_symbol];

    return value;
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
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

    return myconv.to_bytes(ws);
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
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

    return myconv.to_bytes(ws);
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
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

    return myconv.to_bytes(ws);
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




 std::vector<std::string> utf8_splitter(const std::string& line, UTF8_SPLITER_ERROR& error) {
     std::vector<std::string> result;
     size_t i = 0;
     size_t length = line.size();

     while (i < length) {
         unsigned char byte = line[i];

         // Single-byte character (ASCII)
         if ((byte & 0b10000000) == 0b00000000) {
             result.emplace_back(1, byte);
             i++;
         }
         // Two-byte character
         else if ((byte & 0b11100000) == 0b11000000) {
             if (i + 1 < length
                 && ((line[i + 1] & 0b11000000) == 0b10000000)) {
                 result.emplace_back(line.substr(i, 2));
                 i += 2;
             }
             else {
                 error = UTF8_SPLITER_ERROR::NOT_HAVE_ENOUGH_SIZE;
                 return result;
             }
         }
         // Three-byte character
         else if ((byte & 0b11110000) == 0b11100000) {
             if (i + 2 < length
                 && ((line[i + 1] & 0b11000000) == 0b10000000)
                 && ((line[i + 2] & 0b11000000) == 0b10000000)) {
                 result.emplace_back(line.substr(i, 3));
                 i += 3;
             }
             else {
                 error = UTF8_SPLITER_ERROR::NOT_HAVE_ENOUGH_SIZE;
                 return result;
             }
         }
         // Four-byte character
         else if ((byte & 0b11111000) == 0b11110000) {
             if (i + 3 < length
                 && ((line[i + 1] & 0b11000000) == 0b10000000)
                 && ((line[i + 2] & 0b11000000) == 0b10000000)
                 && ((line[i + 3] & 0b11000000) == 0b10000000)) {
                 result.emplace_back(line.substr(i, 4));
                 i += 4;
             }
             else {
                 error = UTF8_SPLITER_ERROR::NOT_HAVE_ENOUGH_SIZE;
                 return result;
             }
         }
         // Unsupported symbol
         else {
             error = UTF8_SPLITER_ERROR::UNSUPORTED_SYMBOL;
             return result;
         }
     }

     error = UTF8_SPLITER_ERROR::NOTHING;  // No errors
     return result;
 }

 std::pair<uint8_t, UTF8_to_CP1251_CONVERTER_ERROR> convert_utf8_toUTF8cp1251(const std::string& symbol) {

     const static robin_hood::unordered_flat_map<std::string, uint8_t> utf8_to_utf8cp1251{
         {u8" ",0x20},{u8"!",0x21},{u8"\"",0x22},{u8"#",0x23},{u8"$",0x24},{u8"%",0x25},{u8"&",0x26},{u8"\'",0x27},{u8"(",0x28},{u8")",0x29},{u8"*",0x2a},{u8"+",0x2b},{u8",",0x2c}, {u8"-",0x2d},{u8".",0x2e},{u8"/",0x2f},
         {u8"0",0x30},{u8"1",0x31},{u8"2",0x32}, {u8"3",0x33},{u8"4",0x34},{u8"5",0x35},{u8"6",0x36},{u8"7",0x37}, {u8"8",0x38},{u8"9",0x39},{u8":",0x3a},{u8";",0x3b},{u8"<",0x3c}, {u8"=",0x3d},{u8">",0x3e},{u8"?",0x3f},
         {u8"@",0x40},{u8"A",0x41},{u8"B",0x42}, {u8"C",0x43},{u8"D",0x44},{u8"E",0x45},{u8"F",0x46},{u8"G",0x47}, {u8"H",0x48},{u8"I",0x49},{u8"J",0x4a},{u8"K",0x4b},{u8"L",0x4c}, {u8"M",0x4d},{u8"N",0x4e},{u8"O",0x4f},
         {u8"P",0x50},{u8"Q",0x51},{u8"R",0x52}, {u8"S",0x53},{u8"T",0x54},{u8"U",0x55},{u8"V",0x56},{u8"W",0x57}, {u8"X",0x58},{u8"Y",0x59},{u8"Z",0x5a},{u8"[",0x5b},{u8"\\",0x5c},{u8"]",0x5d},{u8"^",0x5e},{u8"_",0x5f},
         {u8"`",0x60},{u8"a",0x61},{u8"b",0x62}, {u8"c",0x63},{u8"d",0x64},{u8"e",0x65},{u8"f",0x66},{u8"g",0x67}, {u8"h",0x68},{u8"i",0x69},{u8"j",0x6a},{u8"k",0x6b},{u8"l",0x6c}, {u8"m",0x6d},{u8"n",0x6e},{u8"o",0x6f},
         {u8"p",0x70},{u8"q",0x71},{u8"r",0x72}, {u8"s",0x73},{u8"t",0x74},{u8"u",0x75},{u8"v",0x76},{u8"w",0x77}, {u8"x",0x78},{u8"y",0x79},{u8"z",0x7a},{u8"{",0x7b},{u8"|",0x7c}, {u8"}",0x7d},{u8"~",0x7e},
         {u8"Ä",0x80},{u8"Å",0x81},{u8"Ç",0x82}, {u8"É",0x83},{u8"Ñ",0x84},{u8"Ö",0x85},{u8"Ü",0x86},{u8"á",0x87}, {u8"à",0x88},{u8"â",0x89},{u8"ä",0x8a},{u8"ã",0x8b},{u8"å",0x8c}, {u8"ç",0x8d},{u8"é",0x8e},{u8"è",0x8f},
         {u8"ê",0x90},{u8"ë",0x91},{u8"í",0x92}, {u8"ì",0x93},{u8"î",0x94},{u8"ï",0x95},{u8"ñ",0x96},{u8"ó",0x97}              ,{u8"ô",0x99},{u8"ö",0x9a},{u8"õ",0x9b},{u8"ú",0x9c}, {u8"ù",0x9d},{u8"û",0x9e},{u8"ü",0x9f},
                      {u8"°",0xa1},{u8"¢",0xa2}, {u8"£",0xa3},{u8"§",0xa4},{u8"•",0xa5},{u8"¶",0xa6},{u8"ß",0xa7}, {u8"®",0xa8},{u8"©",0xa9},{u8"™",0xaa},{u8"´",0xab},{u8"¨",0xac},              {u8"Æ",0xae},{u8"Ø",0xaf},
         {u8"∞",0xb0},{u8"±",0xb1},{u8"≤",0xb2}, {u8"≥",0xb3},{u8"¥",0xb4},{u8"µ",0xb5},{u8"∂",0xb6},{u8"∑",0xb7}, {u8"∏",0xb8},{u8"π",0xb9},{u8"∫",0xba},{u8"ª",0xbb},{u8"º",0xbc}, {u8"Ω",0xbd},{u8"æ",0xbe},{u8"ø",0xbf},
         {u8"¿",0xc0},{u8"¡",0xc1},{u8"¬",0xc2}, {u8"√",0xc3},{u8"ƒ",0xc4},{u8"≈",0xc5},{u8"∆",0xc6},{u8"«",0xc7}, {u8"»",0xc8},{u8"…",0xc9},{u8" ",0xca},{u8"À",0xcb},{u8"Ã",0xcc}, {u8"Õ",0xcd},{u8"Œ",0xce},{u8"œ",0xcf},
         {u8"–",0xd0},{u8"—",0xd1},{u8"“",0xd2}, {u8"”",0xd3},{u8"‘",0xd4},{u8"’",0xd5},{u8"÷",0xd6},{u8"◊",0xd7}, {u8"ÿ",0xd8},{u8"Ÿ",0xd9},{u8"⁄",0xda},{u8"€",0xdb},{u8"‹",0xdc}, {u8"›",0xdd},{u8"ﬁ",0xde},{u8"ﬂ",0xdf},
         {u8"‡",0xe0},{u8"·",0xe1},{u8"‚",0xe2}, {u8"„",0xe3},{u8"‰",0xe4},{u8"Â",0xe5},{u8"Ê",0xe6},{u8"Á",0xe7}, {u8"Ë",0xe8},{u8"È",0xe9},{u8"Í",0xea},{u8"Î",0xeb},{u8"Ï",0xec}, {u8"Ì",0xed},{u8"Ó",0xee},{u8"Ô",0xef},
         {u8"",0xf0},{u8"Ò",0xf1},{u8"Ú",0xf2}, {u8"Û",0xf3},{u8"Ù",0xf4},{u8"ı",0xf5},{u8"ˆ",0xf6},{u8"˜",0xf7}, {u8"¯",0xf8},{u8"˘",0xf9},{u8"˙",0xfa},{u8"˚",0xfb},{u8"¸",0xfc}, {u8"˝",0xfd},{u8"˛",0xfe},{u8"ˇ",0xff},
     };
     auto it = utf8_to_utf8cp1251.find(symbol);

     if (it != utf8_to_utf8cp1251.end()) {
         return { it->second,UTF8_to_CP1251_CONVERTER_ERROR::NOTHING };
     }
     else {
         return { 0,UTF8_to_CP1251_CONVERTER_ERROR::UNSUPPORTED_SYMBOL };
     }


 }