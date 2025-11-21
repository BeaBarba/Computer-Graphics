#include "Scena.h"

/* Variabili Da Importare */
/* Finestra */
extern int window_width, window_height;
extern float window_width_background, window_height_background;

void costruisciScena(vector<Figura>* Scena) {

	Figura background;
	background.nTriangles = 2;
	/* Inizializza la posizione nel mondo */
	background.position = vec3(0.0, 0.0, 0.0);
	/* Definisco il nome della figura per riconoscerla */
	background.nome = BACKGROUND;
	/* Inizializza la geometria del piano */
	INIT_PIANO(&background, vec4(0.0, 1.0, 0.5, 1.0));
	/* Inizializza le matrici di trasformazione */
	background.Model = mat4(1.0);
	background.scale = vec3((float)window_width_background, (float)window_height_background, 1.0);//vec3((float)window_width, (float)window_height, 1.0);
	background.Model = scale(background.Model, background.scale);
	/* Inizializza il VAO della figura */
	INIT_VAO(&background);
	/* Aggiunge al vector Scena la struttura di tipo Figura piano */
	Scena->push_back(background);
}