#version 450
layout(location = 3) in vec2 Tex;
layout(location = 4) out vec4 FragColor;

uniform vec3 color;
void main()
{
	FragColor = vec4(color, 1.0);
}