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

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 N = normalize(vNormal);
	vec3 L = normalize(light.pos - fragPos);
	vec3 H = normalize(L + viewDir);

	float diff = max(dot(N, L), 0.0);
	vec3 diffuse = uMaterial.diffuse * diff * light.color;

	float spec = pow(max(dot(N, H), 0.0), uMaterial.shininess);
	vec3 specular = uMaterial.specular * spec * light.color;

	float	distance = length(light.pos - fragPos);
	float	attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	diffuse *= attenuation;
	specular *= attenuation;
	return (diffuse + specular);
}

vec3 CalcSunLight(vec3 normal, vec3 fragPos, vec3 sunDir, vec3 sunColor)
{
	vec3 sunLightDir = normalize(-sunDir);

	float diff = max(dot(normalize(normal), sunLightDir), 0.0);
	return (diff * sunColor);
}

void main()
{
	vec3 viewDir = normalize(uViewPos - vWorldPos);

	vec4 materialColor = vec4(vec3(1), uMaterial.opacity);
	if (uMaterial.hasDiffuseTex == 1)
		materialColor = texture(tex, vUV);

	vec3 result = vec3(0);
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(uLight[i], vNormal, vWorldPos, viewDir);

	result += CalcSunLight(vNormal, vWorldPos, vec3(-0.5, -1, -0.25), vec3(1));

	materialColor.rgb = materialColor.rgb * clamp(result, 0.0, 1.0);

	FragColor = materialColor;
}
