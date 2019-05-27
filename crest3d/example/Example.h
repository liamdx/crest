#pragma once

#include "CrestCore.h"

class Example {
public:

	virtual ~Example() {};
	virtual void initBehaviour() {};
	virtual void startBehaviour() {};
	virtual void earlyUpdateBehaviour(float deltaTime) {};
	virtual void fixedUpdateBehaviour() {};
	virtual void updateBehaviour(float deltaTime) {};

	// should we pass view matrix through the render pass?
	// ease passing the view matrix from camera around, 
	// could be done in a better way?
	virtual void renderBehaviour(float deltaTime) {};
	virtual void uiBehaviour(float deltaTime) {};

};