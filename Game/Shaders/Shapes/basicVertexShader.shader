#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 uModel;  // TRS matrix
uniform mat4 uView;   // camera transform
uniform mat4 uProj; // projection

out vec4 vertexColor;

void main()
{
	gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
	vertexColor = aColor;
};