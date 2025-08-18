#ifndef PROCESSRUNER_H
#define PROCESSRUNER_H

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "Utils/Synchronization/CriticalSection/CriticalSection.h"



class ProcessRuner
{
public:
	~ProcessRuner();
	ProcessRuner(const std::wstring& Path2Executable);
	ProcessRuner();

	void SetPath(const std::wstring& Path2Executable);
	void SetArgs(const std::wstring& args);


	void Run();
	void Run(const std::wstring& args);
	void Run(const std::wstring& args, const std::wstring& dir);
	void Terminate();


	std::vector<std::string> GetOutput();
	void SetInput(const std::wstring& input);
	void SetInput(const std::string& input);

	bool IsOutputChanged();

	bool IsRunning();
	
private:
	std::wstring Path2Executable;
	std::wstring str_args;

	bool flag_IsRunning = false;



	HANDLE hThread;
	SECURITY_ATTRIBUTES sa;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	void Close();


	struct ThreadData {
		CriticalSection cs_cout_from_process;
		std::vector<std::string> stream_output;
		HANDLE hStdoutRead, hStdoutWrite;
		HANDLE hStdinRead,  hStdinWrite;
		bool ProcessClosed = false;
	} data_thread;

	static DWORD WINAPI ThreadReader(LPVOID lpParam);

	void Init();
};




#endif //!PROCESSRUNER_H