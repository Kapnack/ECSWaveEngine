#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

layout(location = 4) in mat4 instanceModel;
layout(location = 8) in vec3 aTangent;

out vec4 vColor;
out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPos;
out vec3 vTangent;

uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    vColor = aColor;
    vTexCoord = aTexCoord;

    gl_Position = uProj * uView * instanceModel * vec4(aPos, 1.0);
    vFragPos = vec3(instanceModel * vec4(aPos, 1.0));

    mat3 normalMatrix = mat3(transpose(inverse(instanceModel)));
    vNormal     = normalMatrix * aNormal;
    vTangent    = normalMatrix * aTangent;
}