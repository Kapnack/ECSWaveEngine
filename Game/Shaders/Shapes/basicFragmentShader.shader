	#version 330 core

	in vec4 vertexColor;

	uniform vec4 uColor;

	out vec4 FragColor;

	void main()
	{
		FragColor = vertexColor * uColor;
	};