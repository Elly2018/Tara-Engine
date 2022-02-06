#version 420
in vec2 Tex;
out vec4 FragColor;

uniform vec3 color;
void main()
{
	FragColor = vec4(color, 1.0);
}