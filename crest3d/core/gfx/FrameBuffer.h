#pragma once
#include "Shader.h"
class FrameBuffer
{
public:
	FrameBuffer() {}

	~FrameBuffer() {}

	void initialise(float SCREEN_WIDTH, float, bool multiSample);

	void changeScreenSize(float newWidth, float newHeight);

	void initForDrawing();
	void finishDrawing();

	inline int GetTexture() { return framebufferTexture; }
	inline int GetDepthTexture() { return depthTexture; }
	inline int GetFBO() { return fbo; }
	inline int GetRBO() { return rbo; }

	// Shader color = GL Texture Slot 7
	void BindColorTexture(Shader shader);
	// Shader depth = GL Texture Slot 8
	void BindDepthTexture(Shader shader);

private:
	float screenWidth, screenHeight;
	unsigned int fbo, rbo, msFbo;
	unsigned int framebufferTexture, msFramebufferTexture, depthTexture;

	bool isMultiSample;

};