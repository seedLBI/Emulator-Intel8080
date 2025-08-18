#ifndef I8080_UI_TIMER_H
#define I8080_UI_TIMER_H

#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include <string>


class Widget_Timer : public I8080_Widget
{
public:
	Widget_Timer(I8080* processor);
	~Widget_Timer();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	I8080* processor;
};


#endif // !I8080_UI_TIMER_H
