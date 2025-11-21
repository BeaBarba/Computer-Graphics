#pragma once

#include <glad/glad.h>						// Loader per funzioni OpenGL (carica puntatori a funzioni OpenGL)
#include <GLFW/glfw3.h>						// Libreria per gestione finestre, input, context OpenGL
#include <ImGui\imgui.h>					// Libreria ImGui per GUI immediate mode
#include <ImGui\imgui_impl_glfw.h>			// Integrazione ImGui con GLFW (input e finestre)
#include <ImGui\imgui_impl_opengl3.h>		// Integrazione ImGui con OpenGL3 (rendering)
#include <vector>							// Classe del C per agevolare operazioni sui vettori
#include <glm/glm.hpp>						// Libreria GML per le matrici di trasformazione
#include <glm/gtc/matrix_transform.hpp>		// Libreria GML per le funzioni di trasformazione delle matrici
#include <glm/gtc/type_ptr.hpp>				// Libreria GML per le funzioni di conversione delle matrici
#include <fstream>							// Loader per funzioni di lettura dei file
#include <iostream>							// Input/output standard C++


using namespace std;
using namespace glm;

#define PI 3.14159265358979323