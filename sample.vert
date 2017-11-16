#version 330 core
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vel;
layout(location = 2) in vec4 color;

//uniform mat4 projection;
//uniform mat4 view;
//uniform mat4 model;
uniform vec4 gravity;

out vec3 oColor;

void main()
{
	//mat4 mvp = projection * view * model;
	//mat4 mvp = projection * model;
	vec3 scale = vec3(1.0, 16.0 / 9.0, 1.0);
	gl_Position = vec4(scale * vertexPosition.xyz, 1);
	float len = clamp(length(gravity.xyz - vertexPosition.xyz), 0.0, 1.0);
	oColor = vec3(1.0 - len * 0.25, 1.0 - len * 0.5, 0.0);
	//oColor = clamp(abs(vertexPosition.xyz), 0.0, 1.0);
	//oColor = color.xyz;
	//oColor = (vertexPosition.xyz + 1.0) / 2.0;
}
