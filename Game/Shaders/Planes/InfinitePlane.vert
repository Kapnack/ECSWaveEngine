#version 330 core

layout(location = 0) in vec2 aPos;

uniform mat4 uInvViewProj;

out vec3 vNearPoint;
out vec3 vFarPoint;

vec3 UnprojectPoint(float x, float y, float z, mat4 invViewProj)
{
    vec4 p = invViewProj * vec4(x, y, z, 1.0);
    return p.xyz / p.w;
}

void main()
{
    vNearPoint = UnprojectPoint(aPos.x, aPos.y, -1.0, uInvViewProj);
    vFarPoint  = UnprojectPoint(aPos.x, aPos.y,  1.0, uInvViewProj);

    gl_Position = vec4(aPos, 0.0, 1.0);
}
