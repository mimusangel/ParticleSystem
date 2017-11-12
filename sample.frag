#version 330 core

out vec4 color;

in vec3 oVel;

void main(){
	color = vec4(oVel, 1.0);
}
