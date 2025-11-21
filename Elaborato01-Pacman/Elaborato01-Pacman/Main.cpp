/*
	Progetto di Barba Beatrice - Primo Elaborato per l'esame di Computer Graphics
	Simulazione del pacman molto semplificato
*/

#include "lib.h"				// Header file con tutte le librerie di configurazione del progetto necessarie			
#include "Gui.h"				// Header file della GUI personalizzata
#include "ShaderMaker.h"		// Header file della classe che gestisce gli Shader
#include "Rendering.h"			// Header file della funzione di rendering

/*----------------------------------------------------------------*/

/* Variabili globali */
/* Esterne */
extern float x_offset, y_offset;

/* Colori */
ImVec4 clear_color_1 = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);			// Colore di pulizia prima schermata (RGBA)
ImVec4 clear_color_2 = ImVec4(0.0f, 1.0f, 0.5f, 1.0f);			// Colore di pulizia seconda schermata (RGBA)

/* Finestra */
int window_width = 1000, window_height = 800;					// Risoluzione finesta iniziale

/* Gui */
bool button_set = false;										// Flag per cambiare interfaccia

/* Shader */
unsigned int program_id;										// Identificativo del program shader

GLuint id_proj, id_model;										// Identificativi per le matrici di modellazione e proiezione da usare negli shader

int main(void) {

	/* Creazione della finestra */
	GLFWwindow* window;

	/* Inizializza libreria GLFW */
	if (!glfwInit()) {
		return -1;
	}

	/* Setta OpenGL e il profile core */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	/* Inizializzazione della finestra con contesto OpenGL */
	window = glfwCreateWindow(window_width, window_height, "Pac - man", NULL, NULL);

	/* Controllo della creazione della finestra */
	if (!window) {
		cout << "Creazione della finestra fallita" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	/* Caricamento puntatori OpenGL tramite GLAD per la portabilità */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Caricamento dei puntatori OpenGl fallito" << endl;
		glfwTerminate();
		return -1;
	}

	/* Abilitazione del framebuffer sRGB */
	glEnable(GL_FRAMEBUFFER_SRGB);

	/* Inizializzazione ImGui con la finestra GLFW */
	InitializeImGui(window);

	/* Inizializzo gli shader */
	program_id = ShaderMaker::initShader((char*)"vertexShader.glsl", (char*)"fragmentShader.glsl");

	/* Registrazione dei callback per gli eventi */

	/* Gameloop */
	while (!glfwWindowShouldClose(window)) {

		/* Disegna la scena */
		rendering();

		/* Renderizza la GUI ImGui */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Scambio dei buffer */
		glfwSwapBuffers(window);

		/* Cattura e processazione degli eventi input */
		glfwPollEvents();
	}

	/* Pulizia finale */
	closeGUI();
	glfwDestroyWindow(window);
	glDeleteProgram(program_id);
	glfwTerminate();
	return 0;
}
