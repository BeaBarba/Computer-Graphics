#pragma once

#include "lib.h"
#include <ImGui\imgui.h>                // Libreria core ImGui
#include <ImGui\imgui_impl_glfw.h>      // Integrazione ImGui con GLFW (gestione finestra/input)
#include <ImGui\imgui_impl_opengl3.h>   // Integrazione ImGui con OpenGL3 (rendering)
#include <math.h>						// Libreria matematica standard C

void InitializeImGui(GLFWwindow* window);
void interfaceMenu(void);
void interfaceGame(void);
void closeGUI(void);