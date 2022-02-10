#version 420
in vec2 Tex;
out vec4 FragColor;

uniform vec3 color;
uniform sampler2D surface;
void main()
{
	FragColor = texture(surface, Tex) * vec4(color, 1.0);
}