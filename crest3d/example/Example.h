#pragma once

#include "CrestCore.h"

class Example {
public:
	Example();
	virtual ~Example() {};

	Scene mainScene;

	virtual void startBehaviour() {};
	virtual void earlyUpdateBehaviour() {};
	virtual void updateBehaviour() {};
	virtual void uiBehaviour() {};

};