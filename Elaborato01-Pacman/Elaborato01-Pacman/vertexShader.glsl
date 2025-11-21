#version 330 core // Versione GLSL utilizzata

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 Color;

uniform mat4 Projection;
uniform mat4 Model;

out vec4 color_frag;


void main(){
	
	gl_Position = Projection * Model * vec4(aPos, 1.0);
	color_frag = Color;

}