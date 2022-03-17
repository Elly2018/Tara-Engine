#version 430
#extension GL_ARB_shading_language_include : require
#extension GL_ARB_enhanced_layouts : enable

layout (location = 0) out vec4 diffuseColor;
layout (location = 4) out VertexData {
	vec3 Tex;
} fs_in;

layout (binding = 4) uniform samplerCube skybox;

void main(){
    diffuseColor = texture(skybox, fs_in.Tex);
}