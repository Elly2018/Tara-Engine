#version 430
#extension GL_ARB_shading_language_include : require
#extension GL_ARB_enhanced_layouts : enable
#include "/base/Utility.glsl"
#include "/base/Model.glsl"

layout (location = 4) out VertexData {
	vec3 Tex;
} vs_out;

void main(){
    Tex = aPos;
    gl_Position = projection * view * vec4(aPos, 1.0);
}