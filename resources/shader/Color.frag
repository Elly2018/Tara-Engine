#version 430
#extension GL_ARB_shading_language_include : require
#extension GL_ARB_enhanced_layouts : enable

layout (location = 0) out vec4 diffuseColor;
layout (location = 4) in VertexData {
	vec3 FragPos;
	vec2 Tex;
	vec3 Normal;
} vs_in;
layout (binding = 5) uniform ColorData {
	vec3 color;
} colorData;

void main()
{
	diffuseColor = vec4(colorData.color, 1.0);
}