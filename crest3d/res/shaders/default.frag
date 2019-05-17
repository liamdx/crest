#version 440

in vec3 normal;
in vec3 fragPosition;
in vec2 vTexCoords;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
