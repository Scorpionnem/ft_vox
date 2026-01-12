#version 330 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vUV;
in vec3 vWorldPos;

out vec4 FragColor;

struct Material
{
	vec3	ambient;

	vec3	diffuse;
	int		hasDiffuseTex;

	vec3	specular;

	float	shininess;
	float	opacity;
};

struct Light {
	vec3	pos;

	vec3	color;

	float	constant;
	float	linear;
	float	quadratic;
};

#define NR_POINT_LIGHTS_MAX 32
uniform int	NR_POINT_LIGHTS;
uniform Light	uLight[NR_POINT_LIGHTS_MAX];

uniform Material uMaterial;

uniform vec3 uViewPos;

uniform float uTime;

uniform int uTriangleCount;
// Use gl_PrimitiveID for triangle view mode

uniform sampler2D tex;

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewPos)
{
	vec3	norm = normalize(normal);
	vec3	lightDir = normalize(light.pos - fragPos);
	float	diff = max(dot(norm, lightDir), 0.0);
	vec3	diffuse = light.color * (diff * uMaterial.diffuse);

	vec3	viewDir = normalize(viewPos - fragPos);
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
	vec3	specular = light.color * (spec * uMaterial.specular);

	float	distance = length(light.pos - fragPos);
	float	attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	diffuse *= attenuation;
	specular *= attenuation;
	return (diffuse + specular);
}

vec3 CalcSunLight(vec3 normal, vec3 fragPos, vec3 sunDir, vec3 sunColor)
{
	vec3 sunLightDir = normalize(-sunDir);
	vec3 normNormal = normalize(normal);

	float diff = max(dot(normalize(normNormal), sunLightDir), 0.0);
	return (sunColor * (diff * uMaterial.diffuse));
}

uniform float	horizontalRenderDistance;
uniform float	verticalRenderDistance;

uniform float	uSpawnFade;

void main()
{
	vec3 viewDir = normalize(uViewPos - vWorldPos);

	vec4 materialColor = vec4(vec3(1), uMaterial.opacity);
	if (uMaterial.hasDiffuseTex == 1)
		materialColor = texture(tex, vUV);

	vec3	sunColor = vec3(1);
	float	ambientIntensity = 0.2;

	vec3 result = sunColor * ambientIntensity;
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(uLight[i], vNormal, vWorldPos, uViewPos);

	result += CalcSunLight(vNormal, vWorldPos, vec3(-0.5, -1, -0.25), sunColor);

	vec3	fogColor = vec3(0.6, 0.8, 1.0);
	int		fogPower = 4;

	float	fogFactorHorizontal = pow(length(uViewPos.xz - vWorldPos.xz) / horizontalRenderDistance, fogPower);
	fogFactorHorizontal = clamp(fogFactorHorizontal, 0.0, 1.0);

	float	fogFactorVertical = pow(length(uViewPos.y - vWorldPos.y) / verticalRenderDistance, fogPower);
	fogFactorVertical = clamp(fogFactorVertical, 0.0, 1.0);

	materialColor.rgb = materialColor.rgb * clamp(result, 0.0, 1.0);

	FragColor = vec4(mix(mix(materialColor.rgb, fogColor, fogFactorHorizontal), fogColor, fogFactorVertical), materialColor.a);
	FragColor.rgb = mix(FragColor.rgb, fogColor, uSpawnFade);
}
