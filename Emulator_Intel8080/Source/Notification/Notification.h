#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <vector>
#include <string>
#include "Utils/MathUtils.h"
#include "imgui.h"
#include "OpenglWindow/OpenglWindow.h"

#include "Notification/interface/Notification.Element.h"
#include "Notification.Message.h"
#include "Notification.Progress.h"



class Notification
{
private:

	std::vector<N_Element*> elements;


	ImU32 BackgroundColor;
	ImVec4 Raw_BackgroundColor;

	float AnimAlpha = 0.f;

	float DieTime = 0.2f;
	float LifeTime = 1.f; // in seconds;
	float Time = 0.f;

	ImVec2 Pos {0,0};
	ImVec2 AnimPos {0,0};
	float force_Lerp = 10.f;


	ImVec2 notification_padding = ImVec2(10.0f, 10.0f);
	ImVec2 element_padding = ImVec2(10.0f, 10.0f);

	ImVec2 notification_size {0,0};

	ImVec2 rect_min {0,0};
	ImVec2 rect_max {0,0};


	bool* ptr_time_infinity = nullptr;

	void CalculateSizeContent();

public:
	static int objectCount;

	Notification() = default;

	Notification(const ImVec4& BackgroundColor, const float& LifeTime);

	Notification(const ImVec4& BackgroundColor, const float& LifeTime, const std::vector<N_Element*>& elements, bool* ptr_time_infinity);

	~Notification();

	void AddElements(const std::vector<N_Element*>& new_elements);
	void AddElement(N_Element* new_element);

	ImVec2 GetSize();
	ImVec2 GetLerpPos();

	void SetBackgroundColor(const ImVec4& color);
	void SetForceLerping(const float& new_force);
	void SetPos(const ImVec2& new_pos);

	void Draw();

	void Update();

	bool isEnd();

	void Kill();
	void Kill_Immediately();

	bool Contains(const ImVec2& Point);
	
};

#endif

