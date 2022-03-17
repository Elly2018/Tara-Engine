#version 430
#extension GL_ARB_shading_language_include : require
#extension GL_ARB_enhanced_layouts : enable
#include "/base/Utility.glsl"
#include "/base/Model.glsl"

layout (location = 4) out VertexData {
	vec3 FragPos;
	vec2 Tex;
	vec3 Normal;
} vs_out;

void main()
{
	gl_Position = mvp * vec4(aPos, 1.0);
	vs_out.FragPos = vec3(aMatrix * vec4(aPos, 1.0));
	vs_out.Tex = aTex;
	vs_out.Normal = mat3(transpose(inverse(aMatrix))) * aNormal;
}
