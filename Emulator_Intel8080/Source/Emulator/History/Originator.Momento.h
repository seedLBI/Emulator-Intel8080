#ifndef ORIGINATOR_MOMENTO_H
#define ORIGINATOR_MOMENTO_H

#include "Momento.h"
#include <memory>

class Originator_Momento{
public:
	virtual std::shared_ptr<Momento> SaveState();
	virtual void					 RestoreState(const std::shared_ptr<Momento>& momento);
};

#endif // !ORIGINATO_MOMENTO_H
