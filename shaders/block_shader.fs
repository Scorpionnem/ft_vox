#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D textureAtlas;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float time;

void main()
{
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;


	//diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec4 texColor = texture(textureAtlas, TexCoord);

	vec3 result = (ambient + diffuse);
	FragColor = vec4(result, 1.0) * texColor;
};
