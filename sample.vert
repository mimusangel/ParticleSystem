#version 330 core
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vel;
layout(location = 2) in vec4 color;

uniform mat4 projection;
//uniform mat4 view;
uniform mat4 model;

out vec3 oColor;

void main()
{
	//mat4 mvp = projection * view * model;
	mat4 mvp = projection * model;
	gl_Position = mvp * vec4(vertexPosition.xyz, 1);
	oColor = color.xyz; //(vertexPosition.xyz + 1.0) / 2.0;
}
