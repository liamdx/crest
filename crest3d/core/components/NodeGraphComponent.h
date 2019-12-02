#pragma once
#include "nodegraph/NodeGraph.h"
#include "components/EngineComponent.h"

class NodeGraphComponent : public EngineComponent
{
	std::unique_ptr<NodeGraph> nodeGraph;
	
	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void fixedUpdate() override;
	void render(float deltaTime, glm::mat4 view) override;
	void ui(float deltaTime) override;
	
};