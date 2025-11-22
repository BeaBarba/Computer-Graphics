#version 330 core // Versione GLSL utilizzata


in vec4 color_frag;
out vec4 color;

void main(){
	
	//Viene assegnato lo stesso colore ad ogni pixel
	color = color_frag;

}