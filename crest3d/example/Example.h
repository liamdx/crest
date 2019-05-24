#pragma once

#include "CrestCore.h"

class Example {
public:

	virtual ~Example() {};
	virtual void initBehaviour() {};
	virtual void startBehaviour() {};
	virtual void earlyUpdateBehaviour(float deltaTime) {};
	virtual void updateBehaviour(float deltaTime) {};
	virtual void uiBehaviour(float deltaTime) {};

};