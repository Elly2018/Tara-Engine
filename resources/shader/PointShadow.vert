#version 430
#define mvp modelMatrix.projection * modelMatrix.view * aMatrix
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;
layout (location = 3) in mat4 aMatrix;
layout (std140, binding = 2) uniform DepthData {
	mat4 lightMatrix;
} depthData;

void main()
{
	gl_Position = depthData.lightMatrix * aMatrix * vec4(aPos, 1.0);
}