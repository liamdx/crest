#pragma once
#include "Common.h"
#include "gfx/FrameBuffer.h"
#include "RenderGroup.h"

struct RenderPass {
public: 
	RenderPass(Shader* _shader) { shader = _shader; pipe = false; }
	~RenderPass() { delete fb; }
	PropertyGroup properties;

	unsigned int id; // location of the render pass frame buffer
	bool pipe; // is the output of this shader used in the next / future pass
	
private:
	unsigned int resolution_x, resolution_y;
	FrameBuffer* fb;
	Shader* shader;

};

class Pipeline
{
	// must be in sequence. 
	std::vector<RenderPass> passes;
	unsigned int finalImageId; // assumed to be final pass


};