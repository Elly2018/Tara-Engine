#version 430
#extension GL_ARB_shading_language_include : require
#extension GL_ARB_enhanced_layouts : enable
#include "/base/Utility.glsl"
#include "/base/Model.glsl"

void main()
{
	gl_Position = mvp * vec4(aPos, 1.0);
}