#version 330 core

struct DirLight 
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight 
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 vFragPos;
in vec4 vColor;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 FragColor;

uniform vec3 viewPos;

#define MAX_ALBEDO 8
uniform sampler2D uTexture[MAX_ALBEDO];
uniform int uTextureAmount;

#define NR_POINT_LIGHTS 2
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight flashlights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse * diff;
    vec3 specular = light.specular * spec;

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant +
                              light.linear * distance +
                              light.quadratic * distance * distance);

    vec3 ambient  = light.ambient * attenuation;
    vec3 diffuse  = light.diffuse * diff * attenuation;
    vec3 specular = light.specular * spec * attenuation;

    return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant +
                              light.linear * distance +
                              light.quadratic * distance * distance);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient  = light.ambient * attenuation;
    vec3 diffuse  = light.diffuse * diff * attenuation * intensity;
    vec3 specular = light.specular * spec * attenuation * intensity;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(viewPos - vFragPos);

    vec3 result = vec3(0.0);

    result += CalcDirLight(dirLight, norm, viewDir);

    for(int i = 0; i < NR_POINT_LIGHTS; ++i)
    {
        result += CalcPointLight(pointLights[i], norm, vFragPos, viewDir);
    }

    for(int i = 0; i < NR_POINT_LIGHTS; ++i)
        result += CalcSpotLight(flashlights[i], norm, vFragPos, viewDir);
    
    vec4 texColor = vec4(0.0);
    for (int i = 0; i < uTextureAmount; ++i)
        texColor += texture(uTexture[i], vTexCoord);

    FragColor = (texColor * vColor) * vec4(result, 1.0);
}