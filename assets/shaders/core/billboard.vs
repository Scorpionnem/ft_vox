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

uniform vec3 uCenter;
vec3 Size = vec3(0.5);

void main()
{
	vNormal = aNormal;
	vUV = aUV;

	vec3 CameraRight_worldspace = vec3(uView[0][0], uView[1][0], uView[2][0]);
	vec3 CameraUp_worldspace    = vec3(uView[0][1], uView[1][1], uView[2][1]);

	vec3 vertexWorldPos = uCenter + CameraRight_worldspace * aPos.x * Size.x + CameraUp_worldspace    * aPos.y * Size.y;

	vPos = vertexWorldPos;

	gl_Position = uProjection * uView * vec4(vertexWorldPos, 1.0);
}
