#include "MathUtils.h"

void Lerp(ImVec2& from, const ImVec2& to, const float& force_lerp) {

	/*
	float speed_lerp = OpenglWindow::GetDeltaTime() * force_lerp;

	from.x = from.x + speed_lerp * (to.x - from.x);
	from.y = from.y + speed_lerp * (to.y - from.y);
	*/

	float TimesLerping = pow(0.15f/force_lerp, OpenglWindow::GetDeltaTime());

	from.x = to.x + TimesLerping * (from.x - to.x);
	from.y = to.y + TimesLerping * (from.y - to.y);
}

void Lerp(float& from, const float& to, const float& force_lerp) {

	/*
	float speed_lerp = OpenglWindow::GetDeltaTime() * force_lerp;
	from = from + speed_lerp * (to - from);
	*/


	float TimesLerping = pow(0.15f / force_lerp, OpenglWindow::GetDeltaTime());
	from = to + TimesLerping * (from - to);


}
