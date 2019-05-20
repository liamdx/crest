#pragma once
#include "Example.h"

class SimpleExample : public Example
{
public:
	SimpleExample();
	~SimpleExample() override {};
	void startBehaviour() override;
	void earlyUpdateBehaviour() override;
	void updateBehaviour() override;
	void uiBehaviour() override;


	// example vars
};