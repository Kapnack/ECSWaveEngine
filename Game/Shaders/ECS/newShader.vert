#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

layout(location = 3) in mat4 instanceModel;
layout(location = 7) in vec4 aUVOffsetScale;

out vec4 vColor;
out vec2 vTexCoord;

uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    vec2 uv = aTexCoord * aUVOffsetScale.zw + aUVOffsetScale.xy;

    vColor = aColor;
    vTexCoord = uv;

    gl_Position = uProj * uView * instanceModel * vec4(aPos, 1.0);
}