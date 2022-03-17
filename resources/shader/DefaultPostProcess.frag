#version 450
layout (location = 0) out vec4 diffuseColor;
layout (location = 3) in vec2 Tex;

layout (binding = 0) uniform sampler2D screenTexture;

layout (binding = 1) uniform ScreenData {
	vec2 size;
} screenData;

void main()
{
	//FragColor = texture(screenTexture, Tex);
	float uv_x = Tex.x * (screenData.size.x / screenData.size.y);
	float uv_y = Tex.y;
	diffuseColor = vec4(1.0); //texture(screenTexture, Tex);
}