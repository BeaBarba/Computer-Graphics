#include "Rendering.h"

/* Variabili da importare */
/* Colori */
extern ImVec4 clear_color_1, clear_color_2;

/* Finestra */
extern int window_width, window_height;
extern float window_width_background, window_height_background;			// Risoluzione sfondo
extern float x_offset, y_offset;										// Offset per centrare la viewport

/* Shader */
extern GLuint program_id, program_id_background;

/* Scena e matrici di trasformazione */
extern vector<Figura> Scena;
extern mat4 projection, projection_background;

/* Gui */
extern bool button_set;													// Flag bottoni e checkbox dell'interfaccia

/* Tempo */
extern float delta_time;


/* Variabili globali */
/* Tempo */
float last_frame = 0.0;													// Tempo per calcolare il tempo di rendering di un frame

void rendering(float current_time) {
	vec4 colorA, colorB;

	/* Pulizia del buffer del colore di sfondo */
	if (!button_set) {
		glClearColor(clear_color_1.x, clear_color_1.y, clear_color_1.z, clear_color_1.w);
	}
	else {
		glClearColor(clear_color_2.x, clear_color_2.y, clear_color_2.z, clear_color_2.w);
	}
	glClear(GL_COLOR_BUFFER_BIT);

	/* Configurazione del tempo di caricamento di un frame */
	delta_time = current_time - last_frame;
	last_frame = current_time;

	/* Disegna una delle tre interfacce */
	if (button_set) {

		/* ---------------------------------------- Gioco Attivo ------------------------------------- */
		interfaceGame();

		/* Renderizza la GUI ImGui */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Cambia la ViewPort solo per lo sfondo */
		glViewport(0, 0, window_width_background, window_height_background);
		Scena[BACKGROUND].scale = vec3(window_width_background, window_height_background, 1.0);
		Scena[BACKGROUND].Model = mat4(1.0);
		Scena[BACKGROUND].Model = scale(Scena[BACKGROUND].Model, Scena[BACKGROUND].scale);
		ShaderMaker::useShaderWithUniform(
			program_id_background,
			projection_background,
			Scena[BACKGROUND].Model,
			current_time,
			vec2(window_width_background, window_height_background),
			true,
			true
		);

		glBindVertexArray(Scena[BACKGROUND].VAO);

		/* Fa il rendering dello sfondo */
		glDrawArrays(Scena[BACKGROUND].render, 0, Scena[BACKGROUND].nv);

	}
	else {
		/* ---------------------------------------- Inizio Gioco ------------------------------------- */
		interfaceMenu();

		/* Renderizza la GUI ImGui */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}