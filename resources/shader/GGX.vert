#version 450
#define mvp modelMatrix.projection * modelMatrix.view * aMatrix
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;
layout (location = 3) in mat4 aMatrix;
layout (location = 4) out VertexData {
	vec3 FragPos;
	vec2 Tex;
	vec3 Normal;
} vs_out;
layout (std140, binding = 0) uniform Utility {
	float delta;
	float time;
} utility;
layout (std140, binding = 1) uniform ModelMatrix {
	mat4 view;
	mat4 projection;
} modelMatrix;

void main()
{
	gl_Position = mvp * vec4(aPos, 1.0);
	vs_out.FragPos = vec3(aMatrix * vec4(aPos, 1.0));
	vs_out.Tex = aTex;
	vs_out.Normal = mat3(transpose(inverse(aMatrix))) * aNormal;
}