#version 330

uniform float size;

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;

out vec3 color;

void main()
{
	gl_Position = vec4(vPos.x + vPos.x * size, vPos.y + vPos.y * size, vPos.z + vPos.z * size, 1.0);
	color = vColor;
}
