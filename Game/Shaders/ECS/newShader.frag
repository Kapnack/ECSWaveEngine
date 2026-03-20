#version 330 core

in vec4 vColor;
in vec2 vTexCoord;
flat in int vTexID;

out vec4 FragColor;

uniform sampler2D uTextures[16];

void main()
{
    vec4 texColor = texture(uTextures[vTexID], vTexCoord);
    FragColor = texColor * vColor;
}