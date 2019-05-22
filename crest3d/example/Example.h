#pragma once

#include "CrestCore.h"

class Example {
public:

	virtual ~Example() {};

	virtual void startBehaviour() {};
	virtual void earlyUpdateBehaviour() {};
	virtual void updateBehaviour() {};
	virtual void uiBehaviour() {};

};