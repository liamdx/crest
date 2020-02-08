#pragma once

#include "Common.h"

#include "components/MeshComponent.h"

class Shadowmap
{
public:
	enum ShadowmapType {
		directional,
		point,
		spot
	};

	Shadowmap(ShadowmapType _type);
	Shadowmap(ShadowmapType _type, unsigned int _resolution);
	~Shadowmap() {};

	void start();
	void renderLightView(glm::vec3 cameraPosition, std::vector<MeshComponent> meshes);

	inline void setProjection(glm::mat4 newProjection) { projection = newProjection; }
	inline void setView(glm::mat4 newView) { view = newView; }

private:
	unsigned int shadowResolution;
	unsigned int depthMap, depthMapFBO;
	ShadowmapType type;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 lightSpaceMatrix;
};
