#pragma once

class FrameBuffer
{
public:
	FrameBuffer(){}

	~FrameBuffer() {};

	void initialise(float SCREEN_WIDTH, float SCREEN_HEIGHT);
	void changeScreenSize(float newWidth, float newHeight);

	void initForDrawing();
	void finishDrawing();

	inline int GetTexture() { return framebufferTexture; }
	inline int GetFBO() { return fbo; }
	inline int GetRBO() { return rbo; }

private:
	float screenWidth, screenHeight;
	unsigned int fbo, rbo, framebufferTexture;

};