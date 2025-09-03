#ifndef _DEBUG﻿
	//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Application/Application.h"


int main(int argc, char* argv[]) {

	Application app;
	app.Run();
	return 0;

}

