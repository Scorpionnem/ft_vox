#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
	vec4	txColor = texture(screenTexture, TexCoords);

	vec3	color = txColor.rgb;
	FragColor = vec4(vec3(color), 1.0);
}
