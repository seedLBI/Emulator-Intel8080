#ifndef AUTHORPOPUP_H
#define AUTHORPOPUP_H

#include "OpenglTexture.h"

#include "ThirdParty/ImGui/imgui.h"

#include <windows.h>
#include <shellapi.h>

#include "Utils/ImGui.Utils.h"

#include "Data/Images/AuthorPicture/Image.Author.Backend.h"
#include "Data/Images/AuthorPicture/Image.Author.Close.h"
#include "Data/Images/AuthorPicture/Image.Author.EyeTransparent.h"
#include "Data/Images/AuthorPicture/Image.Author.Front.h"
#include "Data/Images/AuthorPicture/Image.Author.LeftEye.h"
#include "Data/Images/AuthorPicture/Image.Author.RightEye.h"





class AuthorPopup
{
public:
	AuthorPopup();
	~AuthorPopup();

	void Draw();

	void Open();

private:

	bool isOpen = false;

	ImVec2 SizePicture{ 460, 458 };




	OpenglTexturee Backend;
	OpenglTexturee Close;
	OpenglTexturee EyeTransparent;
	OpenglTexturee Front;
	OpenglTexturee LeftEye;
	OpenglTexturee RightEye;





	void DrawEyes(ImVec2 PosDraw,const ImVec2& SizeImage, const float& aspect);


};




#endif


