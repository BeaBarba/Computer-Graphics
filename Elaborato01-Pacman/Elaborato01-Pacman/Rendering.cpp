#include "Rendering.h"

/* Variabili da importare */
/* Colori */
extern ImVec4 clear_color_1, clear_color_2;

/* Finestra */
extern int window_width, window_height;
extern float window_width_background, window_height_background;			// Risoluzione sfondo
extern float window_width_update, window_height_update;					// Risoluzione finestra aggiornata
extern float x_offset, y_offset;										// Offset per centrare la viewport

/* Shader */
extern GLuint program_id, program_id_background;

/* Scena e matrici di trasformazione */
extern vector<Figura> Scena;
extern mat4 projection, projection_background;
extern float angolo;													// Angolo di rotazione

/* Gui */
extern bool button_set;													// Flag bottoni e checkbox dell'interfaccia

/* Tempo */
extern float delta_time;


/* Variabili globali */
/* Tempo */
float last_frame = 0.0;													// Tempo per calcolare il tempo di rendering di un frame

void rendering(float current_time) {

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

		/* Riconfigura la ViewPort iniziale con un aspect ratio */
		glViewport(x_offset, y_offset, window_width_update, window_height_update);

		/* Disegna la finestra di gioco */
		posizionaOrientaScala(&Scena[FINESTRA], 0.0);
		ShaderMaker::useShaderWithUniform(program_id, projection, Scena[FINESTRA].Model, 0.0, vec2(window_width_update, window_height_update), false, false);
		glBindVertexArray(Scena[FINESTRA].VAO);
		glDrawArrays(Scena[FINESTRA].render, 0, Scena[FINESTRA].nv);


		/* Animazione Pacman */
		Scena[PACMAN].vertices.clear();
		Scena[PACMAN].colors.clear();
		/* Cambia numero di triangoli con cui disegnarlo per creare un'animazione */
		Scena[PACMAN].nTriangles = 30 + (int)(190 * (sin(current_time*15) + 1) / 2);
		INIT_PACMAN(0.0, 0.0, 0.2, 0.2, &Scena[PACMAN], vec4(1.0, 1.0, 0.0, 1.0), vec4(1.0, 0.9, 0.0, 1.0));
		INIT_VAO(&Scena[PACMAN]);
		posizionaOrientaScala(&Scena[PACMAN], angolo);
		ShaderMaker::useShaderWithUniform(program_id, projection, Scena[PACMAN].Model, 0.0, vec2(window_width, window_height), false, false);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Associa il Vertex Array Object (VAO) della forma, che contiene i dati dei vertici da disegnare
		glBindVertexArray(Scena[PACMAN].VAO);
		glDrawArrays(Scena[PACMAN].render, 0, Scena[PACMAN].nv);
		
		for (int i = 3; i < Scena.size(); i++) {
		
			posizionaOrientaScala(&Scena[i], 0.0);
			ShaderMaker::useShaderWithUniform(program_id, projection, Scena[i].Model, 0.0, vec2(window_width, window_height), false, false);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			// Associa il Vertex Array Object (VAO) della forma, che contiene i dati dei vertici da disegnare
			glBindVertexArray(Scena[i].VAO);
			glDrawArrays(Scena[i].render, 0, Scena[i].nv);
		
		}

	}
	else {
		/* ---------------------------------------- Inizio Gioco ------------------------------------- */
		interfaceMenu();

		/* Renderizza la GUI ImGui */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}