#version 330 core

in vec4 vColor;
in vec2 vTexCoord;
in vec3 vModel;

out vec4 FragColor;

uniform sampler2D uTexture;
uniform float AmbientStrength;
uniform vec3 LightColor;

void main()
{
    vec4 texColor = texture(uTexture, vTexCoord);

    vec3 ambient = AmbientStrength * LightColor;

    FragColor = (texColor * vColor) * vec4(ambient, 1.0f);
}