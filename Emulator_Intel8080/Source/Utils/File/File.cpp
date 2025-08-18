#include "File.h"


bool isFileExist(const std::wstring& PathFile) {
    std::ifstream ifn(PathFile);
    bool result = ifn.good();
    ifn.close();
    return result;
}

bool isFileExist(const std::string& PathFile) {
    return isFileExist(stringUTF8_to_wstring(PathFile));
}

bool isFileExist(const std::ifstream& Fstream_File) {
    return Fstream_File.good();
}

bool isFileNotEmpty(std::ifstream& Fstream_File) {
    return !(Fstream_File.peek() == std::ifstream::traits_type::eof());
}

bool HaveFolder(const std::wstring& Path) {
    return std::filesystem::is_directory(Path);
}

bool CreateFolder(const std::wstring& Path){
    std::filesystem::path dir(Path);

    if (std::filesystem::create_directory(dir))
        return true;
    else
        return false;
}

std::vector<uint8_t> ReadFileToByteArray(const std::string& filePath) {
    std::ifstream file(stringUTF8_to_wstring(filePath), std::ios::binary);
    if (!file.is_open()) {
        return {};
    }

    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> byteArray(fileSize);

    if (!file.read(reinterpret_cast<char*>(byteArray.data()), fileSize)) {
        throw std::runtime_error(u8"Ошибка при чтении файла");
    }
    file.close();
    return byteArray;
}

std::vector<std::string> ReadTextFromFile(const std::string& PathFile) {
    return ReadTextFromFile(stringUTF8_to_wstring(PathFile));
}

std::vector<std::string> ReadTextFromFile(const std::wstring& PathFile) {
    std::ifstream ifn(PathFile);

    std::vector<std::string> result;

    std::string line;

    while (std::getline(ifn, line)) {
        result.push_back(line);
    }

    return result;
}

std::string GetPathApplication() {
    CHAR path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return path;
}

std::wstring GetPathDirectory() {
    return std::filesystem::current_path().wstring();
}


/// <summary>
/// Filter формат: "Название\0*.file1;*.file2\0"
/// </summary>
/// <param name="TitleWindow - название окна"></param>
/// <param name="Filter - фильтр для файлов"></param>
/// <returns></returns>
std::string Save_FileDialog(const std::string& TitleWindow, const std::string& Filter) {
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

    std::wstring w_Filter = std::wstring(Filter.begin(), Filter.end());
    ofn.lpstrFilter = w_Filter.c_str();


    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    // Display the Open dialog box. 

    std::wstring w_TitleWindow = std::wstring(TitleWindow.begin(), TitleWindow.end());

    ofn.lpstrTitle = w_TitleWindow.c_str();

    if (GetSaveFileName(&ofn) == TRUE) {

    }




    //std::wstring ws(szFile);
    //std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

    //return myconv.to_bytes(ws);


    return wstring_to_stringUTF8(szFile);
}


/// <summary>
/// Filter формат: "Название\0*.file1;*.file2\0"
/// </summary>
/// <param name="TitleWindow - название окна"></param>
/// <param name="Filter - фильтр для файлов"></param>
/// <returns></returns>
std::wstring Open_FileDialog(const wchar_t* TitleWindow, const wchar_t* Filter, const wchar_t* defaultPath) {
    OPENFILENAME ofn{};
    wchar_t szFile[460] = {};
    HWND hwnd = GetConsoleWindow();

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = _countof(szFile);


    ofn.lpstrFilter = Filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrTitle = TitleWindow;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
    if (defaultPath != nullptr) {
        ofn.lpstrInitialDir = defaultPath;
    }


    if (GetOpenFileName(&ofn) == TRUE) {
        return szFile;
    }

   

    return std::wstring();
}

std::wstring Open_FolderDialog(const wchar_t* TitleWindow, const wchar_t* defaultPath) {
    std::wstring folderPath;
    HWND owner = GetConsoleWindow();
    IFileDialog* pFileDialog = nullptr;

    // Инициализируем COM
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)))
        return L"";


    // Создаём экземпляр FileOpenDialog
    if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pFileDialog)))) {
        // Устанавливаем только выбор папок
        DWORD options;
        if (SUCCEEDED(pFileDialog->GetOptions(&options))) {
            pFileDialog->SetOptions(options | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM);
        }

        // Устанавливаем заголовок
        pFileDialog->SetTitle(TitleWindow);
        

        // Устанавливаем начальный путь, если он указан
        if (defaultPath != nullptr) {
            IShellItem* pDefaultFolder = nullptr;
            if (SUCCEEDED(SHCreateItemFromParsingName(defaultPath, nullptr, IID_PPV_ARGS(&pDefaultFolder)))) {
                pFileDialog->SetFolder(pDefaultFolder);
                pDefaultFolder->Release();
            }
        }

        // Показываем диалог
        if (SUCCEEDED(pFileDialog->Show(owner))) {
            IShellItem* pItem = nullptr;
            if (SUCCEEDED(pFileDialog->GetResult(&pItem))) {
                PWSTR pszFolder = nullptr;
                if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFolder))) {
                    folderPath = pszFolder;
                    CoTaskMemFree(pszFolder);
                }
                pItem->Release();
            }
        }
        pFileDialog->Release();
    }

    CoUninitialize();
    return folderPath;
}

