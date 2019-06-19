#pragma once
#include "components/EngineComponent.h"

class ShaderComponent;

class LightComponent : public EngineComponent
{
public:
	virtual void Bind(std::shared_ptr<ShaderComponent>) {} ;
};
