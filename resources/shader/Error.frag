#version 430
#extension GL_ARB_shading_language_include : require
#extension GL_ARB_enhanced_layouts : enable
layout (location = 0) out vec4 diffuseColor;

void main()
{
	diffuseColor = vec4(1.0, 0.0, 1.0, 1.0);
}