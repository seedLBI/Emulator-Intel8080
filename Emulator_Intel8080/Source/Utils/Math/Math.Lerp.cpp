#include "Math.Lerp.h"


void Lerp(ImColor& from, const ImColor& to, const float& force_lerp, const float& deltaTime) {
	float TimesLerping = std::pow(0.15f / force_lerp, deltaTime);

	from.Value.x = to.Value.x + TimesLerping * (from.Value.x - to.Value.x);
	from.Value.y = to.Value.y + TimesLerping * (from.Value.y - to.Value.y);
	from.Value.z = to.Value.z + TimesLerping * (from.Value.z - to.Value.z);
	from.Value.w = to.Value.w + TimesLerping * (from.Value.w - to.Value.w);
}


void Lerp(ImVec2& from, const ImVec2& to, const float& force_lerp, const float& deltaTime) {
	float TimesLerping = std::pow(0.15f/force_lerp, deltaTime);

	from.x = to.x + TimesLerping * (from.x - to.x);
	from.y = to.y + TimesLerping * (from.y - to.y);
}

void Lerp(float& from, const float& to, const float& force_lerp, const float& deltaTime) {
	float TimesLerping = std::pow(0.15f / force_lerp, deltaTime);
	from = to + TimesLerping * (from - to);
}
