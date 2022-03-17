#version 430
#extension GL_ARB_shading_language_include : require
#extension GL_ARB_enhanced_layouts : enable
#include "/base/Light.glsl"

layout (location = 0) out vec4 diffuseColor;
layout (location = 4) in VertexData {
	vec3 FragPos;
	vec2 Tex;
	vec3 Normal;
	vec3 LightPos[4];
	vec4 FragPosLightSpace[4];
} fs_in;

layout (binding = 4) uniform TextureData {
	vec2 offset;
	vec2 scale;
	vec3 tint;
} textureData;

layout (binding = 4) uniform sampler2D surface;

void main()
{
	vec3 ambient = lightData.ambient.xyz * lightData.ambient.w;

	vec3 diffuse = vec3(0.0);
	float sha = 0;
	vec3 viewDir = normalize(lightData.eye - fs_in.FragPos);
	float specularStrength = 0.5;

	for (int i = 0; i < 4; i++) {
		Light li = lightData.light[i];
		vec3 lightDir = normalize(li.position - fs_in.FragPos);

		if(li.lightType == 0){
			// Direction
			float difu = max(dot(fs_in.Normal, normalize(li.direction)), 0.0);
			diffuse += li.color.xyz * li.color.w * difu;
			sha += ShadowCalculation(fs_in.LightPos[i], GetShadowDepth(i), fs_in.FragPosLightSpace[i], fs_in.Normal, fs_in.FragPos);
		}else if(li.lightType == 1){
			// Point
			float dis = distance(li.position, fs_in.FragPos);
			float attenuation = 1.0 / (1.0 + 0.09 * dis + 
    		    0.032 * (dis * dis));
			float difu = max(dot(fs_in.Normal, normalize(li.position - fs_in.FragPos)), 0.0);
			diffuse += li.color.xyz * li.color.w * difu * attenuation;
		}else if(li.lightType == 2){
			// Spot
		}
	}
	sha = max(1.0, sha);

	vec2 actualTex = (fs_in.Tex + textureData.offset) * textureData.scale;
	vec4 texColor = texture(surface, actualTex);
	//diffuseColor = vec4(ambient + diffuse + spec, 1.0) * texColor;
	diffuseColor = vec4(ambient + (1.0 - (sha * 0.5)) * diffuse, 1.0) * texColor;
	//diffuseColor = vec4(vec3(fs_in.FragPosLightSpace[1]), 1.0);
	//diffuseColor = texColor;
}