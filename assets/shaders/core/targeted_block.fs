#version 330 core

out vec4 FragColor;

uniform float uTime;

void main()
{
	FragColor = vec4(vec3(1), 0.1 + abs(sin(uTime * 4) / 2));
}
