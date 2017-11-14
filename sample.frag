#version 330 core

out vec4 color;

in vec3 oColor;

void main(){
	color = vec4(clamp(oColor, 0.2, 1.0), 1.0);
}
