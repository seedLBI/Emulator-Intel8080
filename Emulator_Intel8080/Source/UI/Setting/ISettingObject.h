#ifndef ISETTING_OBJECT_H
#define ISETTING_OBJECT_H

#include "ISettingSavable.h"
#include "ISettingDrawable.h"

class ISettingObject: public ISettingDrawable, public ISettingSavable {
public:
	ISettingObject(const std::string& NameObject, const std::string& NameTab);
	void DrawBegin();
};


#endif // !ISETTING_OBJECT_H
