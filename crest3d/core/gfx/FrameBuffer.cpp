#include "FrameBuffer.h"
#include "Common.h"

void FrameBuffer::initialise(float SCREEN_WIDTH, float SCREEN_HEIGHT)
{
	glViewport(0,0,screenWidth, screenHeight);
	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;

	//Frame buffer set up
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// FULL Forward pass
	glGenTextures(1, &framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

	// depth attachment
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, screenWidth, screenHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
	glDrawBuffers(2, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void FrameBuffer::changeScreenSize(float newWidth, float newHeight)
{
	screenWidth = newWidth;
	screenHeight = newHeight;

	initialise(screenWidth, screenHeight);
}

void FrameBuffer::initForDrawing()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // | GL_STENCIL_BUFFER_BIT included
}

void FrameBuffer::finishDrawing() 
{
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	
}

void FrameBuffer::BindColorTexture(Shader shader)
{
	glActiveTexture(GL_TEXTURE7);
	shader.setInt("screenTexture", 7);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
}

void FrameBuffer::BindDepthTexture(Shader shader)
{
	glActiveTexture(GL_TEXTURE8);
	shader.setInt("depthTexture", 8);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
}

