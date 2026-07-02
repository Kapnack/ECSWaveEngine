#version 330 core

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
struct SpotLight {
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
in vec3 vTangent;

out vec4 FragColor;

uniform vec3 viewPos;

// ── Albedo ───────────────────────────────────────────────────────────────────
uniform sampler2D uAlbedo;
uniform bool      hasuAlbedo;
uniform vec4      uMatColor;

// ── PBR maps (NEW) ───────────────────────────────────────────────────────────
uniform sampler2D uNormalMap;
uniform bool      hasuNormalMap;

uniform sampler2D uRoughnessMap;
uniform bool      hasuRoughnessMap;
uniform float     uRoughness;       // fallback scalar

uniform sampler2D uMetallicMap;
uniform bool      hasuMetallicMap;
uniform float     uMetallic;        // fallback scalar

uniform sampler2D uAOMap;
uniform bool      hasuAOMap;

uniform sampler2D uEmissiveMap;
uniform bool      hasuEmissiveMap;
uniform vec3      uEmissiveColor;   // fallback / tint
uniform float     uEmissiveStrength;

#define NR_POINT_LIGHTS 2
uniform DirLight  dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight  flashlights[NR_POINT_LIGHTS];

// ── Fresnel (Schlick approximation) ─────────────────────────────────────────
vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

// ── Energy-conserving specular ───────────────────────────────────────────────
// Returns (diffuse, specular) contributions from one light direction.
// Diffuse is suppressed for metals; specular is tinted by F0.
void CalcBRDF(vec3 lightDir, vec3 normal, vec3 viewDir,
              vec3 F0, float metallic, float roughness,
              out vec3 outDiff, out vec3 outSpec)
{
    float shininess = mix(2.0, 256.0, 1.0 - roughness);
    float diff      = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float RdotV     = max(dot(reflectDir, viewDir), 0.0);
    float spec      = pow(RdotV, shininess);

    // Fresnel at this light angle — uses half-vector cosine for accuracy
    vec3 halfVec    = normalize(lightDir + viewDir);
    vec3 F          = FresnelSchlick(max(dot(halfVec, viewDir), 0.0), F0);

    // Energy conservation: diffuse and specular can't together exceed 1
    vec3 kS = F;
    vec3 kD = (1.0 - kS) * (1.0 - metallic);   // metals have no diffuse

    outDiff = kD * diff;
    outSpec = kS * spec;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir,
                  vec3 F0, float metallic, float roughness)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 diffC, specC;
    CalcBRDF(lightDir, normal, viewDir, F0, metallic, roughness, diffC, specC);

    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diffC;
    vec3 specular = light.specular * specC;
    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir,
                    vec3 F0, float metallic, float roughness)
{
    vec3  lightDir    = normalize(light.position - fragPos);
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant +
                                light.linear    * distance +
                                light.quadratic * distance * distance);
    vec3 diffC, specC;
    CalcBRDF(lightDir, normal, viewDir, F0, metallic, roughness, diffC, specC);

    vec3 ambient  = light.ambient  * attenuation;
    vec3 diffuse  = light.diffuse  * diffC * attenuation;
    vec3 specular = light.specular * specC * attenuation;
    return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir,
                   vec3 F0, float metallic, float roughness)
{
    vec3  lightDir    = normalize(light.position - fragPos);
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant +
                                light.linear    * distance +
                                light.quadratic * distance * distance);
    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 diffC, specC;
    CalcBRDF(lightDir, normal, viewDir, F0, metallic, roughness, diffC, specC);

    vec3 ambient  = light.ambient  * attenuation;
    vec3 diffuse  = light.diffuse  * diffC * attenuation * intensity;
    vec3 specular = light.specular * specC * attenuation * intensity;
    return ambient + diffuse + specular;
}

void main()
{
    // ── 1. Albedo ─────────────────────────────────────────────────────────────
    vec4 texColor = hasuAlbedo ? texture(uAlbedo, vTexCoord) : uMatColor;
    vec3 albedo   = texColor.rgb * vColor.rgb;
    float alpha   = texColor.a  * vColor.a;

    // Alpha cutout — discard fully transparent fragments
    if (alpha < 0.01) 
        discard;

    // ── 2. Normal mapping ─────────────────────────────────────────────────────
    vec3 norm;
    if (hasuNormalMap)
    {
        // Build TBN matrix from interpolated tangent + normal
        vec3 N   = normalize(vNormal);
        vec3 T   = normalize(vTangent - dot(vTangent, N) * N);  // Gram–Schmidt
        vec3 B   = cross(N, T);
        mat3 TBN = mat3(T, B, N);

        vec3 sampledNormal = texture(uNormalMap, vTexCoord).rgb;
        sampledNormal      = sampledNormal * 2.0 - 1.0;         // [0,1] → [-1,1]
        norm               = normalize(TBN * sampledNormal);
    }
    else
    {
        norm = normalize(vNormal);
    }

    // ── 3. PBR parameters ────────────────────────────────────────────────────
    float roughness = hasuRoughnessMap
        ? texture(uRoughnessMap, vTexCoord).r
        : uRoughness;

    float metallic  = hasuMetallicMap
        ? texture(uMetallicMap,  vTexCoord).r
        : uMetallic;

    // F0: dielectrics reflect ~4%, metals reflect their own albedo color
    vec3 F0 = mix(vec3(0.04), albedo, metallic);

    // ── 4. Lighting ───────────────────────────────────────────────────────────
    vec3 viewDir = normalize(viewPos - vFragPos);
    vec3 result  = vec3(0.0);

    result += CalcDirLight(dirLight, norm, viewDir, F0, metallic, roughness);
    for (int i = 0; i < NR_POINT_LIGHTS; ++i)
        result += CalcPointLight(pointLights[i], norm, vFragPos, viewDir, F0, metallic, roughness);
    for (int i = 0; i < NR_POINT_LIGHTS; ++i)
        result += CalcSpotLight(flashlights[i], norm, vFragPos, viewDir, F0, metallic, roughness);

    // ── 5. Albedo tint ────────────────────────────────────────────────────────
    // Diffuse albedo still tints the lit result; metallic surfaces lose their
    // diffuse contribution but keep the specular tint via F0 above.
    vec3 color = albedo * result;

    // ── 6. Ambient Occlusion ──────────────────────────────────────────────────
    if (hasuAOMap)
    {
        float ao = texture(uAOMap, vTexCoord).r;
        color   *= ao;      // darkens occluded crevices
    }

    // ── 7. Emissive ───────────────────────────────────────────────────────────
    vec3 emissive = hasuEmissiveMap
        ? texture(uEmissiveMap, vTexCoord).rgb * uEmissiveColor
        : uEmissiveColor;

    color += emissive * uEmissiveStrength;

    // ── 8. Gamma correction (linear → sRGB, γ = 2.2) ─────────────────────────
    color = pow(max(color, 0.0), vec3(1.0 / 2.2));

    FragColor = vec4(color, alpha);
}