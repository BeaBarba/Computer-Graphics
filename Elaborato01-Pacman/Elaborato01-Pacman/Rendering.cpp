
#include "Rendering.h"

/* Variabili da importare */
/* Colori */
extern ImVec4 clear_color_1, clear_color_2;

/* Finestra */
extern int window_width, window_height;

/* Shader */
extern GLuint program_id;

/* Gui */
extern bool button_set;								// Flag bottoni e checkbox dell'interfaccia

void rendering() {
	vec4 colorA, colorB;

	/* Pulizia del buffer del colore di sfondo */
	if (!button_set) {
		glClearColor(clear_color_1.x, clear_color_1.y, clear_color_1.z, clear_color_1.w);
	}
	else {
		glClearColor(clear_color_2.x, clear_color_2.y, clear_color_2.z, clear_color_2.w);
	}
	glClear(GL_COLOR_BUFFER_BIT);

	
	/* Disegna una delle tre interfacce */
	if (button_set) {

		/* ---------------------------------------- Gioco Attivo ------------------------------------- */
		interfaceGame();

		/* Renderizza la GUI ImGui */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	else {
		/* ---------------------------------------- Inizio Gioco ------------------------------------- */
		interfaceMenu();

		/* Renderizza la GUI ImGui */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}