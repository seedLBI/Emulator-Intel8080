#ifndef I8080_UI_OUTPUT_0X02_H
#define I8080_UI_OUTPUT_0X02_H

#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include "Core/Emulator/Port/ConsoleOutput/ConsoleOutput.Port.h"

#include "Utils/ImGui/Utils.ImGui.h"

#include "GUI/Notification/NotificationManager.h"

#include <string>
#include <vector>




class Widget_Output0x02: public I8080_Widget
{
public:
	Widget_Output0x02(I8080* processor,NotificationManager* notificationManager);
	~Widget_Output0x02();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	NotificationManager* notificationManager;

	bool mode_output = true;

	bool Hex_enable = false;
	bool Dec_enable = true;
	bool Bin_enable = false;
	bool Char_enable = false;


	I8080* processor;
};






#endif // !I8080_UI_OUTPUT_0X02_H
