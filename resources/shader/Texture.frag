#version 430
#extension GL_ARB_shading_language_include : require
#extension GL_ARB_enhanced_layouts : enable

layout (location = 0) out vec4 diffuseColor;
layout (location = 4) in vec2 Tex;
layout (binding = 3) uniform TextureData {
	vec2 offset;
	vec2 scale;
	vec3 tint;
} textureData;
layout (binding = 0) uniform sampler2D surface;

void main()
{
	vec2 actualTex = (Tex + textureData.offset) * textureData.scale;
	diffuseColor = texture(surface, actualTex) * vec4(textureData.tint, 1.0);
}