#version 440

layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoords;
layout (location=2) in vec3 inNormal;
layout (location=3) in ivec4 BoneIDs;
layout (location=4) in vec4 Weights;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const int MAX_NUMBER_OF_BONES = 250;
const int MAX_NUMBER_OF_WEIGHTS = 4;

uniform mat4 gBones[MAX_NUMBER_OF_BONES];

out vec2 TexCoords;
out vec3 Normal;
out vec3 WorldPos;


void main()
{
	// mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
    // BoneTransform     += gBones[BoneIDs[1]] * Weights[1];
    // BoneTransform     += gBones[BoneIDs[2]] * Weights[2];
    // BoneTransform     += gBones[BoneIDs[3]] * Weights[3];

    // vec4 PosL    = BoneTransform * vec4(position, 1.0);
    // WorldPos = vec3(model * PosL);
    // gl_Position  = projection * view * model * PosL;
    // TexCoords   = texCoords;
    // vec4 NormalL = BoneTransform * vec4(inNormal, 0.0);
    // Normal      =  NormalL;

    vec4 totalLocalPos = vec4(0.0);
	vec4 totalNormal = vec4(0.0);
	
	for(int i=0;i<MAX_NUMBER_OF_WEIGHTS;i++){
		mat4 jointTransform = gBones[BoneIDs[i]];
		vec4 posePosition = jointTransform * vec4(position, 1.0);
		totalLocalPos += posePosition * Weights[i];
		
		vec4 worldNormal = jointTransform * vec4(inNormal, 0.0);
		totalNormal += worldNormal * Weights[i];
	}
	
	gl_Position = projection * view * model * totalLocalPos;
	Normal = totalNormal.xyz;
	TexCoords = texCoords;
    WorldPos = vec3(model * totalLocalPos);
}