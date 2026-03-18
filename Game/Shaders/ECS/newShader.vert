#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexID; // you already have this

out vec4 vColor;
out vec2 vTexCoord;
out float vTexID;

uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    vColor = aColor;
    vTexCoord = aTexCoord;
    vTexID = aTexID;

    gl_Position = uProj * uView * vec4(aPos, 1.0);
}