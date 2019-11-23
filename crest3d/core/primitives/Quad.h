#pragma once
#include "gfx/Model.h"

class Quad
{
public:
	Texture tex;
	Quad(std::string texturePath);

	Quad();
	~Quad();
	void Draw(Shader shader);

	void Draw(Shader shader, const char* uniformName, unsigned int textureLocation);
	float quadVertices[30] = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};

private:
	unsigned int vao, vbo;
};

class screenQuad {
	// usage

	// fbShader.use();
	// fbShader.setFloat("gamma", 1.0);
	// renderQuad.Draw(fbShader, "screenTexture", mainFB.GetTexture());

public:
	screenQuad();
	~screenQuad();

	void Draw(Shader shader, const char* uniformName, unsigned int textureLocation);
private:
	float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							 // positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f, //top left
		-1.0f, -1.0f,  0.0f, 0.0f,//bottom left
		1.0f, -1.0f,  1.0f, 0.0f, //bottom right

		-1.0f,  1.0f,  0.0f, 1.0f, // bottom right
		1.0f, -1.0f,  1.0f, 0.0f, // top left
		1.0f,  1.0f,  1.0f, 1.0f // top right
	};

	unsigned int vao, vbo;
};
