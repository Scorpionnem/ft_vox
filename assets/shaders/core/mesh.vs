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

uniform mat4 uShadowProjection;
uniform mat4 uShadowView;

out vec4 FragPosLightSpace;

void main()
{
	vNormal = aNormal;
	vUV = aUV;
	vPos = aPos;
	vWorldPos = vec4(uModel * vec4(aPos, 1.0)).xyz;

	vec3	fragPos = vec3(uModel * vec4(aPos, 1.0));
	FragPosLightSpace = uShadowProjection * uShadowView * vec4(fragPos, 1.0);

	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
