#version 450
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTex;
layout(location = 3) out vec2 Tex;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	Tex = aTex;
}