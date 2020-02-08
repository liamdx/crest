#pragma once

#include "Common.h"
#include "FrameBuffer.h"

class RenderContext
{

	virtual ~RenderContext() { frames.clear(); }
		
	unsigned int NUM_VIEWS;
	unsigned int numActiveViews;

	std::vector<glm::mat4> projectionMatrices;
	std::vector<glm::mat4> viewMatrices;
	std::vector<FrameBuffer> frames;
	
};