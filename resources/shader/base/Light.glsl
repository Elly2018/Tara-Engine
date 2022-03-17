struct LightMat{
	mat4 lightSpaceMatrix;
	vec3 lightPos;
};

struct Light {
	int lightType;
	vec3 position;
	vec4 color;
	vec3 direction;
};

layout (std140, binding = 2) uniform LightMatrix {
	LightMat lightMat[4];
} lightMatrix;

layout (std140, binding = 3) uniform LightingData {
	vec3 eye;
	vec4 ambient;
	Light light[4];
} lightData;

layout (binding = 0) uniform sampler2D shadows_0;
layout (binding = 1) uniform sampler2D shadows_1;
layout (binding = 2) uniform sampler2D shadows_2;
layout (binding = 3) uniform sampler2D shadows_3;

float ShadowCalculation(vec3 lightPos, sampler2D shadowMap, vec4 fragPosLightSpace, vec3 Normal, vec3 FragPos)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    vec3 lightDir = normalize(lightPos - FragPos);
    float bias = max(0.05 * (1.0 - dot(Normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    // float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

sampler2D GetShadowDepth(int index){
	if(index == 0) return shadows_0;
	else if(index == 1) return shadows_1;
	else if(index == 2) return shadows_2;
	else return shadows_3;
}