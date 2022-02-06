#version 420
#extension GL_ARB_explicit_uniform_location : require
in vec2 Tex;
out vec4 FragColor;

layout(location = 0) uniform sampler2D screenTexture;
uniform vec2 screenSize;

void main()
{
	//FragColor = texture(screenTexture, Tex);
	float uv_x = Tex.x * (screenSize.x / screenSize.y);
	float uv_y = Tex.y;
	FragColor = texture(screenTexture, Tex);
}