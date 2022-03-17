#define mvp modelMatrix.projection * modelMatrix.view * aMatrix
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;
layout (location = 3) in mat4 aMatrix;
layout (std140, binding = 1) uniform ModelMatrix {
	mat4 view;
	mat4 projection;
} modelMatrix;