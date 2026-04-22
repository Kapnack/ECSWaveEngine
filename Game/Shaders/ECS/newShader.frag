#version 330 core

in vec3 vFragPos;
in vec4 vColor;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 FragColor;

uniform vec3 viewPos;
uniform sampler2D uTexture;
uniform vec3 LightPos;
uniform float AmbientStrength;
uniform float SpecularStrength;
uniform vec3 LightColor;

void main()
{
    vec3 normal = normalize(vNormal);
    vec3 lightDir = normalize(LightPos - vFragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * LightColor;

    vec4 texColor = texture(uTexture, vTexCoord);

    vec3 ambient = AmbientStrength * LightColor;

    vec3 viewDir = normalize(viewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, normal); 

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = SpecularStrength * spec * LightColor; 

    vec3 result = ambient + diffuse + specular;

    FragColor = (texColor * vColor) * vec4(result, 1.0f);
}