#ifndef AUTHORPOPUP_H
#define AUTHORPOPUP_H

#include <Windows.h>
#include <shellapi.h>

#include "Utils/OpenGL/Texture/Texture.h"

#include "ThirdParty/ImGui/imgui.h"

#include "Utils/ImGui/Utils.ImGui.h"

#include "Data/Images/AuthorPicture/Image.Author.Backend.h"
#include "Data/Images/AuthorPicture/Image.Author.Close.h"
#include "Data/Images/AuthorPicture/Image.Author.EyeTransparent.h"
#include "Data/Images/AuthorPicture/Image.Author.Front.h"
#include "Data/Images/AuthorPicture/Image.Author.LeftEye.h"
#include "Data/Images/AuthorPicture/Image.Author.RightEye.h"


class AuthorPopup {
public:
	AuthorPopup(GLFWwindow* window);
	~AuthorPopup();

	void Draw();

	void Open();

private:
	GLFWwindow* window = nullptr;
	bool isOpen = false;

	ImVec2 SizePicture{ 460, 458 };

	ImVec2 uv0{ 0,1 };
	ImVec2 uv1{ 1,0 };

	Texture Backend;
	Texture Close;
	Texture EyeTransparent;
	Texture Front;
	Texture LeftEye;
	Texture RightEye;

	void DrawEyes(ImVec2 PosDraw,const ImVec2& SizeImage, const float& aspect);
};




#endif


