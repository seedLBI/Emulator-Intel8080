#ifndef FILE_MAPPING_HPP
#define FILE_MAPPING_HPP

#include <windows.h>
#include <stdexcept>
#include <string>


template<typename T>
class FileMapping {
public:

    FileMapping(const std::wstring& filename, bool createNew = false) {

        DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
        DWORD dwCreationDisposition = createNew ? CREATE_ALWAYS : OPEN_EXISTING;
        
        mappingHandle = OpenFileMapping(dwDesiredAccess, false, L"FILE_MAPPING_DEBUG_CONSOLE");

        if (mappingHandle == NULL)
        {
#ifdef _DEBUG
            std::cout << "File Mapping not exist\n";
            std::cout << "Creating or Open File\n";
#endif // _DEBUG
            fileHandle = CreateFile(
                filename.c_str(),
                dwDesiredAccess,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                nullptr,
                dwCreationDisposition,
                FILE_ATTRIBUTE_NORMAL,
                nullptr
            );

            if (fileHandle == INVALID_HANDLE_VALUE) {
                throw std::runtime_error("Не удалось открыть файл");
            }

#ifdef _DEBUG
            std::cout << "Creating Mapping\n";
#endif // _DEBUG
            mappingHandle = CreateFileMapping(
                fileHandle,
                nullptr,
                PAGE_READWRITE,
                0,
                sizeof(T),
                L"FILE_MAPPING_DEBUG_CONSOLE"
            );

            if (!mappingHandle) {
                CloseHandle(fileHandle);
                throw std::runtime_error("Не удалось создать отображение файла");
            }
        }
        else {
#ifdef _DEBUG
            std::cout << "Opened File Mapping\n";
#endif // _DEBUG
        }


        dataPtr = reinterpret_cast<T*>(MapViewOfFile(
            mappingHandle,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            sizeof(T)
        ));
        if (!dataPtr) {
            CloseHandle(mappingHandle);
            CloseHandle(fileHandle);
            throw std::runtime_error("Не удалось отобразить файл в память");
        }


#ifdef _DEBUG
        std::cout << "File Mapping Full Created\n";
#endif // _DEBUG
    }

    ~FileMapping() {
        if (dataPtr) {
            UnmapViewOfFile(dataPtr);
        }
        if (mappingHandle) {
            CloseHandle(mappingHandle);
        }
        if (fileHandle != INVALID_HANDLE_VALUE) {
            CloseHandle(fileHandle);
        }
    }

    T* get() {
        return dataPtr;
    }

    const T* get() const {
        return dataPtr;
    }

    T& operator*() {
        return *dataPtr;
    }

    const T& operator*() const {
        return *dataPtr;
    }

    T* operator->() {
        return dataPtr;
    }
    const T* operator->() const {
        return dataPtr;
    }

    FileMapping(const FileMapping&) = delete;
    FileMapping& operator=(const FileMapping&) = delete;

private:
    HANDLE fileHandle = INVALID_HANDLE_VALUE;
    HANDLE mappingHandle = nullptr;
    T* dataPtr = nullptr;
};

#endif // FILE_MAPPING_HPP
