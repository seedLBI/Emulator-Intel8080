#include "Notification.h"



int Notification::objectCount = 0;


void Notification::CalculateSizeContent() {
	ImVec2 size{ 0,0 };
	for (int i = 0; i < elements.size(); i++) {
		ImVec2 temp = elements[i]->GetSize();
		if (temp.x > size.x)
			size.x = temp.x;




		size.y += temp.y;
	}

	notification_size = ImVec2(size.x + element_padding.x * 2.f, size.y + element_padding.y * 2.f);


}



Notification::Notification(const ImVec4& BackgroundColor, const float& LifeTime) {
	SetBackgroundColor(BackgroundColor);
	this->LifeTime = LifeTime;
	CalculateSizeContent();
	objectCount++;
}

Notification::Notification(const ImVec4& BackgroundColor, const float& LifeTime, const std::vector<N_Element*>& elements,bool* ptr_time_infinity = nullptr) {
	SetBackgroundColor(BackgroundColor);
	this->LifeTime = LifeTime;
	this->elements = elements;
	CalculateSizeContent();

	if (ptr_time_infinity != nullptr){
		this->ptr_time_infinity = ptr_time_infinity;
	}

	objectCount++;
}

Notification::~Notification() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Notification::~Notification()\n";
#endif // !WITH_DEBUG_OUTPUT
	//for (int i = 0; i < elements.size(); i++)
	//	delete elements[i];
}

void Notification::AddElements(const std::vector<N_Element*>& new_elements) {
	this->elements = new_elements;
	CalculateSizeContent();
}
void Notification::AddElement(N_Element* new_element) {
	elements.push_back(new_element);
	CalculateSizeContent();
}

ImVec2 Notification::GetSize() {
	return notification_size;
}

ImVec2 Notification::GetLerpPos() {
	return AnimPos;
}

void Notification::SetBackgroundColor(const ImVec4& color) {
	Raw_BackgroundColor = color;
	BackgroundColor = IM_COL32(color.x*255.f, color.y * 255.f, color.z * 255.f, (float)color.w * 255.f * AnimAlpha);
}

void Notification::SetForceLerping(const float& new_force) {
	force_Lerp = new_force;
}

void Notification::SetPos(const ImVec2& new_pos) {
	if (AnimPos.x == 0 && AnimPos.y == 0)
		AnimPos = new_pos;
	Pos = new_pos;
}

void Notification::Draw() {

	ImGuiIO& io = ImGui::GetIO();
	ImDrawList* draw_list = ImGui::GetForegroundDrawList();

	ImVec2 window_size = io.DisplaySize;

	rect_min = ImVec2(
		window_size.x - notification_size.x - notification_padding.x,
		window_size.y - notification_size.y - notification_padding.y - AnimPos.y);

	rect_max = ImVec2(
		window_size.x - notification_padding.x,
		window_size.y - notification_padding.y - AnimPos.y);

	
	draw_list->AddRectFilled(rect_min, rect_max, BackgroundColor, 0.0f);


	float AnimProgressLife = (LifeTime - Time) / LifeTime;
	if (AnimProgressLife > 1.f)
		AnimProgressLife = 1.f;
	if (AnimProgressLife < 0.f)
		AnimProgressLife = 0.f;

	ImColor inverseColor = BackgroundColor;
	inverseColor.Value.x = 1.f - inverseColor.Value.x;
	inverseColor.Value.y = 1.f - inverseColor.Value.y;
	inverseColor.Value.z = 1.f - inverseColor.Value.z;


	draw_list->AddRectFilled(rect_min, { rect_min.x + (rect_max.x - rect_min.x)* AnimProgressLife ,rect_min.y + element_padding.y * 0.5f }, inverseColor, 0.0f);


	ImVec2 Rect_Element_min{ rect_min.x + element_padding.x,rect_min.y + element_padding.y };
	ImVec2 Rect_Element_max = { rect_max.x - element_padding.x,rect_max.y - element_padding.y };


	for (int i = 0; i < elements.size(); i++) {
		elements[i]->Draw(draw_list, Rect_Element_min, Rect_Element_max);

		Rect_Element_min.y += elements[i]->GetSize().y;

	}
}

void Notification::Update(const float& deltaTime) {

	if (ptr_time_infinity != nullptr) {
		if (Time >= LifeTime) {
			Time += deltaTime;
		}
		else {
			Time += deltaTime * (*ptr_time_infinity);
		}
	}
	else {
		Time += deltaTime;
	}

	

	if (Time < LifeTime)
		Lerp(AnimAlpha, 1.f, 20.f*force_Lerp, deltaTime);
	else {
		Lerp(AnimAlpha, 1.f - (Time - LifeTime)/DieTime, 20.f*force_Lerp, deltaTime);
	}

	Lerp(AnimPos, Pos, force_Lerp*60.f, deltaTime);


	for (int i = 0; i < elements.size(); i++) {
		elements[i]->SetAlpha(AnimAlpha);
	}

	BackgroundColor = IM_COL32(Raw_BackgroundColor.x * 255.f, Raw_BackgroundColor.y * 255.f, Raw_BackgroundColor.z * 255.f, (float)Raw_BackgroundColor.w * 255.f * AnimAlpha);

	if (Contains(ImGui::GetMousePos())) {

		//ImGui::SetNextWindowFocus();
		//ImGui::Begin("sdsdsdsds",NULL,ImGuiWindowFlags_NoBackground| ImGuiWindowFlags_NoDecoration);
		//ImGui::End();

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
			Kill();
		}
	}
}

bool Notification::isEnd() {
	return Time > LifeTime + DieTime;
}

void Notification::Kill() {
	if (Time < LifeTime)
		Time = LifeTime;
	
}
void Notification::Kill_Immediately() {
	Time = LifeTime + DieTime + 1.f;
}

bool Notification::Contains(const ImVec2& Point) {
	if (Point.x > rect_min.x && Point.x < rect_max.x &&
		Point.y > rect_min.y && Point.y < rect_max.y)
		return true;

	return false;
}