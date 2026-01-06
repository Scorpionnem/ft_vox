#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vNormal;
out vec3 vPos;
out vec2 vUV;
out vec3 vWorldPos;

void main()
{
	vNormal = aNormal;
	vUV = aUV;
	vPos = aPos;
	vWorldPos = vec4(uModel * vec4(aPos, 1.0)).xyz;

	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
