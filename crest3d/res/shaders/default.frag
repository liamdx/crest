#version 330

struct Material {
	sampler2D m_Diffuse;
};

uniform Material mat;

in vec3 normal;
in vec3 fragPosition;
in vec2 vTexCoords;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	vec4 finalColour = texture(ourTexture, vTexCoords);
	//if(finalColour.a < 0.1)
	//	discard;
	FragColor = finalColour;
}
