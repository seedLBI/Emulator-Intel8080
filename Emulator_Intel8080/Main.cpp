/*
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "Config_Compilier.h"
#include "UI/I8080.UI.h"
#include "Scene_Intro/I8080.Scene.Intro.h"
#include "Core/Emulator/Processors/Intel8080/InfoInstruction/InfoInstruction.Data.h"

I8080_UserInterface* i8080_ui = nullptr;

*/

#include "Application/Application.h"


int main(int argc, char* argv[]) {

	Application app;
	app.Run();
	return 0;

	/*
	//setlocale(LC_ALL, "russian");	

	OpenglWindow::Init();

	i8080_ui = new I8080_UserInterface(OpenglWindow::Vars::window);

	std::vector<std::string> arguments = GetArguments(argc, argv);
	if (arguments.size() != 0)
		i8080_ui->OpenFileFromPath(arguments[0]);


	if (i8080_ui->isNeedDrawIntro()) {
		Intro::Init();

#ifdef WITH_DEBUG_OUTPUT
		cout << "Run time: " << glfwGetTime() << endl;
#endif

		while (!glfwWindowShouldClose(OpenglWindow::Vars::window) && Intro::IsEnd() == false) {

			OpenglWindow::BeginDraw();

			if (Intro::FirstMoveAchivied()) {
				i8080_ui->Update();
				i8080_ui->Draw();

			}

			Intro::Update();
			Intro::Draw();
			OpenglWindow::EndDraw();
		}


		Intro::Destructor();
	}

	while (!glfwWindowShouldClose(OpenglWindow::Vars::window) && i8080_ui->ExitButton == false) {
		i8080_ui->Update();


		OpenglWindow::BeginDraw();


		i8080_ui->Draw();


		OpenglWindow::EndDraw();
	}

	i8080_ui->~I8080_UserInterface();



	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	*/
}

