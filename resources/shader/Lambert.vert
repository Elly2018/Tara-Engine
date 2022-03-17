#version 430
#extension GL_ARB_shading_language_include : require
#extension GL_ARB_enhanced_layouts : enable
#include "/base/Utility.glsl"
#include "/base/Model.glsl"
#include "/base/Light.glsl"

layout (location = 4) out VertexData {
	vec3 FragPos;
	vec2 Tex;
	vec3 Normal;
	vec3 LightPos[4];
	vec4 FragPosLightSpace[4];
} vs_out;

void main()
{
	gl_Position = mvp * vec4(aPos, 1.0);
	vs_out.FragPos = vec3(aMatrix * vec4(aPos, 1.0));
	vs_out.Tex = aTex;
	vs_out.Normal = mat3(transpose(inverse(aMatrix))) * aNormal;
	for(int i = 0; i < 4; i++){
		vs_out.FragPosLightSpace[i] = lightMatrix.lightMat[i].lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
		vs_out.LightPos[i] = lightMatrix.lightMat[i].lightPos;
	}
}