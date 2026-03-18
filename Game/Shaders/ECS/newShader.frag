#version 330 core

in vec4 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D uAlbedo;
uniform vec4 uColor;

void main()
{
    vec4 texColor = texture(uAlbedo, vTexCoord);
    FragColor = texColor * vColor * uColor;
}