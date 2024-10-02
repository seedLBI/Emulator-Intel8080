
#include "OpenglWindow.h"

namespace OpenglWindow {

	namespace Vars {
		int FPS_target = 120.f;
		float DeltaaTime = 0.f;
		float Width = 1280.f;
		float Height = 720.f;
		float lasttime = glfwGetTime();



		std::string Title = u8"Ёмул€тор процессора I8080";

		bool FrameBufferSizeWasChanged = false;

		float TimeRender = glfwGetTime();

		GLFWwindow* window;
	}
	namespace Functions {
		void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			Vars::Width = width;
			Vars::Height = height;
			Vars::FrameBufferSizeWasChanged = true;
		}



		void UpdateTimer() {
			OpenglWindow::Vars::DeltaaTime = glfwGetTime() - OpenglWindow::Vars::TimeRender;
			OpenglWindow::Vars::TimeRender = glfwGetTime();

			while (glfwGetTime() < OpenglWindow::Vars::lasttime + 1.0 / OpenglWindow::Vars::FPS_target) {

				//static auto next_frame = std::chrono::steady_clock::now();
				//next_frame += std::chrono::nanoseconds(10);
				//std::this_thread::sleep_until(next_frame);

			}
			OpenglWindow::Vars::lasttime += 1.0 / OpenglWindow::Vars::FPS_target;
		}

		void CenterWindow() {
			// Get the primary monitor
			GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
			if (!primaryMonitor) {
				std::cerr << "Failed to get primary monitor" << std::endl;
				return;
			}

			// Get the monitor's video mode
			const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
			if (!mode) {
				std::cerr << "Failed to get video mode" << std::endl;
				return;
			}

			// Get the window size
			int windowWidth, windowHeight;
			glfwGetWindowSize(OpenglWindow::Vars::window, &windowWidth, &windowHeight);

			// Calculate the position to center the window
			int xpos = (mode->width - windowWidth) / 2;
			int ypos = (mode->height - windowHeight) / 2;

			// Set the window position
			glfwSetWindowPos(OpenglWindow::Vars::window, xpos, ypos);
		}

	}

	bool CheckOpenglError(std::string command) {

		std::unordered_map<GLenum, std::string> error_meanings = {
			{GL_NO_ERROR, "No errors"},
			{GL_INVALID_ENUM, "GL_INVALID_ENUM"},
			{GL_INVALID_VALUE, "GL_INVALID_VALUE"},
			{GL_INVALID_OPERATION, "GL_INVALID_OPERATION"},
			{GL_STACK_OVERFLOW, "GL_STACK_OVERFLOW"},
			{GL_STACK_UNDERFLOW, "GL_STACK_UNDERFLOW"},
			{GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY"},
			{GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION"},
			{GL_CONTEXT_LOST,"GL_CONTEXT_LOST"},
			{GL_TABLE_TOO_LARGE,"GL_TABLE_TOO_LARGE"}
		};



		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			std::cout << "ERROR::" + command + " status: " << error_meanings[err] << std::endl;
			return true;
		}
		return false;
	}
	std::string GetFramebufferErrorMeaning(GLenum status) {
		std::unordered_map<GLenum, std::string> status_meanings = {
			{GL_FRAMEBUFFER_COMPLETE, "Complete"},
			{GL_FRAMEBUFFER_UNDEFINED, "GL_FRAMEBUFFER_UNDEFINED"},
			{GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"},
			{GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"},
			{GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,"GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"},
			{GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,"GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"},
			{GL_FRAMEBUFFER_UNSUPPORTED,"GL_FRAMEBUFFER_UNSUPPORTED"},
			{GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,"GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"},
			{GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS ,"GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS "}
		};
		return status_meanings[status];
	}





	void SetTargetFPS(float FPS) {
		OpenglWindow::Vars::FPS_target = (int)FPS;
	}

	float GetDeltaTime() {
		return OpenglWindow::Vars::DeltaaTime;
	}

	void BeginDraw() {
		OpenglWindow::Functions::UpdateTimer();
		glfwPollEvents();
	}

	void EndDraw() {
		glfwSwapBuffers(OpenglWindow::Vars::window);
	}

	void Init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwSwapInterval(0);


#ifdef WITH_DEBUG_OUTPUT
		std::cout << "Init Glfw window: "; 
#endif
		{
			OpenglWindow::Vars::window = glfwCreateWindow(OpenglWindow::Vars::Width, OpenglWindow::Vars::Height, OpenglWindow::Vars::Title.c_str(), nullptr, nullptr);
			if (OpenglWindow::Vars::window == nullptr) {
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				exit(-1);
			}
#ifdef WITH_DEBUG_OUTPUT
			std::cout << "Success\n";
#endif
		}
		glfwMakeContextCurrent(Vars::window);

#ifdef WITH_DEBUG_OUTPUT
		std::cout << "Init GlEW: ";
#endif
		{
			glewExperimental = GL_TRUE;

			if (glewInit() != GLEW_OK) {
				std::cout << "Failed to initialize GLEW" << std::endl;
				exit(-2);
			}
#ifdef WITH_DEBUG_OUTPUT
			std::cout << "Success\n";
#endif
		}



		GLFWimage images[1];
		int channels = 4;
		images->pixels = SOIL_load_image_from_memory(logo48, 2404, &images[0].width, &images[0].height, &channels, 4);
		glfwSetWindowIcon(OpenglWindow::Vars::window, 1, images);
		OpenglWindow::Functions::CenterWindow();


		glfwSetFramebufferSizeCallback(OpenglWindow::Vars::window, OpenglWindow::Functions::framebuffer_size_callback);

		glViewport(0, 0, OpenglWindow::Vars::Width, OpenglWindow::Vars::Height);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui_ImplGlfw_InitForOpenGL(OpenglWindow::Vars::window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		ImGui::GetIO().IniFilename = NULL;
		ImGui::GetIO().LogFilename = NULL;


	}
};
