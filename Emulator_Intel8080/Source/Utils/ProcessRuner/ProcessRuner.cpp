#include "ProcessRuner.h"

bool ProcessRuner::IsOutputChanged() {
	return data_thread.stream_output.empty() == false;
}

std::vector<std::string> ProcessRuner::GetOutput() {
	std::vector<std::string> Output;
	//std::cout << "enter\n";
	data_thread.cs_cout_from_process.Enter();

		Output = data_thread.stream_output;

		data_thread.stream_output.clear();

	data_thread.cs_cout_from_process.Leave();
	return Output;
}

void ProcessRuner::Terminate() {
	data_thread.ProcessClosed = true;

	if (pi.hProcess != NULL) {
		TerminateProcess(pi.hProcess, 0);
		CloseHandle(pi.hProcess);
		pi.hProcess = NULL;
	}


	WaitForSingleObject(hThread, INFINITE);

	Close();
	flag_IsRunning = false;
}

void ProcessRuner::SetInput(const std::string& input) {
	if (data_thread.hStdinWrite == NULL) {
		std::cout << "Process not created\n";
	}
	else {
		DWORD bytesWritten;


		if (input.back() == '\n')
		{
			std::cout << "INPUT: [" << input.substr(0, input.size() - 1) << "]\n";
		}


		// ONLY STRING!!!!
		if (!WriteFile(data_thread.hStdinWrite, input.data(), DWORD(input.size()), &bytesWritten, NULL)) {
			std::cerr << "WriteFile failed. Error: " << GetLastError() << std::endl;
		}
	}
}

void ProcessRuner::SetInput(const std::wstring& input) {
	SetInput(std::string(input.begin(), input.end()));
}



bool ProcessRuner::IsRunning() {
	if (!flag_IsRunning) return false;

	DWORD exitCode;
	if (GetExitCodeProcess(pi.hProcess, &exitCode)) {

		//std::cout << exitCode << "  " << STILL_ACTIVE << std::endl;

		if (exitCode == STILL_ACTIVE) {
			return true;
		}
		else {
			data_thread.ProcessClosed = true;


			WaitForSingleObject(hThread, INFINITE);
			Close();
			return false;
		}
	}
	else {
		data_thread.ProcessClosed = true;
		std::cout << "Error GetExitCodeProcess :[" << GetLastError() << "]" << std::endl;
		Close();
		return false;
	}
}


void ProcessRuner::Init() {
	data_thread.stream_output.clear();

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;


	if (!CreatePipe(&data_thread.hStdoutRead, &data_thread.hStdoutWrite, &sa, 0)) {
		std::cerr << "Ошибка создания канала stdout: " << GetLastError() << std::endl;
	}

	if (!CreatePipe(&data_thread.hStdinRead, &data_thread.hStdinWrite, &sa, 0)) {
		std::cerr << "Ошибка создания канала stdin: " << GetLastError() << std::endl;
	}

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.hStdOutput = data_thread.hStdoutWrite;
	si.hStdError = data_thread.hStdoutWrite;
	si.hStdInput = data_thread.hStdinRead;
	si.dwFlags = STARTF_USESTDHANDLES;

	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
}



void ProcessRuner::Run(const std::wstring& args, const std::wstring& dir) {
	data_thread.ProcessClosed = false;
	flag_IsRunning = true;

	Init();


	std::wstring FullPath = Path2Executable + L" " + args;

#ifdef _DEBUG
	std::wcout << L"[" << FullPath << "]\n\n";
#endif

	if (!CreateProcessW(NULL, (LPWSTR)FullPath.c_str(), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, (LPWSTR)dir.c_str(), &si, &pi)) {
		std::cerr << "Ошибка запуска процесса: " << GetLastError() << std::endl;

		Close();

		return;

	}

	CloseHandle(data_thread.hStdinRead);
	CloseHandle(data_thread.hStdoutWrite);




	hThread = CreateThread(NULL, 0, ThreadReader, (LPVOID)&data_thread, 0, NULL);

	if (hThread == NULL) {
		std::cerr << "Ошибка создания потока: " << GetLastError() << std::endl;
		TerminateProcess(pi.hProcess, 1);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		Close();
	}
}

void ProcessRuner::Run(const std::wstring& args) {
	data_thread.ProcessClosed = false;
	flag_IsRunning = true;

	Init();


	std::wstring FullPath = Path2Executable + L" " + args;

#ifdef _DEBUG
	std::wcout << L"[" << FullPath << "]\n\n";
#endif

	if (!CreateProcessW(NULL, (LPWSTR)FullPath.c_str(), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
		std::cerr << "Ошибка запуска процесса: " << GetLastError() << std::endl;

		Close();

		return;

	}

	CloseHandle(data_thread.hStdinRead);
	CloseHandle(data_thread.hStdoutWrite);
	



	hThread = CreateThread(NULL, 0, ThreadReader, (LPVOID)&data_thread, 0, NULL);

	if (hThread == NULL) {
		std::cerr << "Ошибка создания потока: " << GetLastError() << std::endl;
		TerminateProcess(pi.hProcess, 1);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		Close();
	}
}

void ProcessRuner::Run() {
	data_thread.ProcessClosed = false;
	flag_IsRunning = true;

	STARTUPINFOW si = { sizeof(si) };
	PROCESS_INFORMATION pi = { 0 };

	std::wstring FullPath = Path2Executable + L" " + str_args;

#ifdef _DEBUG
	std::wcout << L"[" << FullPath << "]\n\n";
#endif

	if (!CreateProcessW(NULL, (LPWSTR)FullPath.c_str(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		std::cerr << "Ошибка запуска процесса: " << GetLastError() << std::endl;
		Close();
		return;

	}

}


void ProcessRuner::Close() {

	if (pi.hProcess != NULL) {
		TerminateProcess(pi.hProcess, 0);
		CloseHandle(pi.hProcess);
		pi.hProcess = NULL;
	}
	if (pi.hThread != NULL) {
		CloseHandle(pi.hThread);
		pi.hThread = NULL;
	}
	if (hThread != NULL) {
		CloseHandle(hThread);
		hThread = NULL;
	}
	if (data_thread.hStdoutRead != NULL) {
		CloseHandle(data_thread.hStdoutRead);
		data_thread.hStdoutRead = NULL;
	}
	if (data_thread.hStdoutWrite != NULL) {
		//CloseHandle(data_thread.hStdoutWrite);
		data_thread.hStdoutWrite = NULL;
	}
	if (data_thread.hStdinRead != NULL)
	{
		//CloseHandle(data_thread.hStdinRead);
		data_thread.hStdinRead = NULL;
	}
	if (data_thread.hStdinWrite != NULL)
	{
		CloseHandle(data_thread.hStdinWrite);
		data_thread.hStdinWrite = NULL;
	}

	flag_IsRunning = false;
}


DWORD WINAPI ProcessRuner::ThreadReader(LPVOID lpParam) {

	ThreadData* data_thread = static_cast<ThreadData*>(lpParam);
	char buffer[1024];
	DWORD bytesRead;
	std::string currentLine;

	while (true) {
		if (ReadFile(data_thread->hStdoutRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
			if (bytesRead > 0) {
				buffer[bytesRead] = '\0';
				currentLine += buffer;

				size_t pos = 0;
				while ((pos = currentLine.find('\n')) != std::string::npos) {
					std::string line = currentLine.substr(0, pos);
					currentLine.erase(0, pos + 1);
					data_thread->cs_cout_from_process.Enter();
					data_thread->stream_output.push_back(line);
					data_thread->cs_cout_from_process.Leave();
				}
			}
		}
		else {
			DWORD error = GetLastError();
			if (error == ERROR_BROKEN_PIPE) {
				// Процесс завершился, и больше данных нет
				break;
			}
			else {
				std::cerr << "ReadFile error: " << error << std::endl;
				break;
			}
		}
	}

	// Добавляем остатки, если они есть
	if (!currentLine.empty()) {
		data_thread->cs_cout_from_process.Enter();
		data_thread->stream_output.push_back(currentLine);
		data_thread->cs_cout_from_process.Leave();
	}

	return 0;

}


ProcessRuner::ProcessRuner(const std::wstring& Path2Executable) {
	this->Path2Executable = Path2Executable;

}

ProcessRuner::ProcessRuner() {

}
void ProcessRuner::SetPath(const std::wstring& Path2Executable) {
	this->Path2Executable = Path2Executable;
}
void ProcessRuner::SetArgs(const std::wstring& args) {
	this->str_args = args;
}



ProcessRuner::~ProcessRuner() {

}