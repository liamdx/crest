#version 440

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 squareVertices;
layout(location = 1) in vec4 xyzs; // Position of the center of the particule and size of the square
layout(location = 2) in vec4 color; // Position of the center of the particule and size of the square

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Position;
out vec4 particlecolor;

// Values that stay constant for the whole mesh.
uniform vec3 camRightWS;
uniform vec3 camUpWS;
uniform mat4 viewProj; // Model-View-Projection matrix, but without the Model (the position is in BillboardPos; the orientation depends on the camera)

void main()
{
	float particleSize = xyzs.w; // because we encoded it this way.
	vec3 particleCenter_wordspace = xyzs.xyz;
	
	vec3 vertexPosition_worldspace = 
		particleCenter_wordspace
		+ camRightWS * squareVertices.x * particleSize
		+ camUpWS * squareVertices.y * particleSize;

	Position = vertexPosition_worldspace;
	// Output position of the vertex
	gl_Position = viewProj * vec4(vertexPosition_worldspace, 1.0);

	// UV of the vertex. No special space for this one.
	UV = squareVertices.xy + vec2(0.5, 0.5);
	particlecolor = color;
}