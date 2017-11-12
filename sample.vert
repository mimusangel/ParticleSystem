#version 330 core
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vel;

out vec3 oVel;

void main()
{
	gl_Position = vec4(vertexPosition.xyz, 1);
	oVel = (vel.xyz + 1.0) / 2.0;
}
