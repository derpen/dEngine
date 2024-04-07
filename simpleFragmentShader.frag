#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D bocchiFace;
uniform sampler2D osakaFace;

void main()
{
	FragColor = mix(texture(bocchiFace, TexCoord), texture(osakaFace, TexCoord), 0.4);
}