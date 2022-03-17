#version 450
#define mvp modelMatrix.projection * modelMatrix.view * modelMatrix.model
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;
layout (location = 3) out vec2 Tex;
layout (std140, binding = 0) uniform Utility{
	float delta;
	float time;
} utility;
layout (std140, binding = 1) uniform ModelMatrix {
	mat4 model;
	mat4 view;
	mat4 projection;
} modelMatrix;

void main()
{
	gl_Position = mvp * vec4(aPos, 1.0);
	Tex = aTex;
}