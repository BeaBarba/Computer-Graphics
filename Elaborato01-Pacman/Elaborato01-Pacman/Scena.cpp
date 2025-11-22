#include "Scena.h"

/* Variabili Da Importare */
/* Finestra */
extern int window_width, window_height;
extern float window_width_background, window_height_background;

/* Matrici di trasformazione */
float angolo = 0.0;
float dx = 0.0, dy = 0.0;

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

	/* Configurazione della finestra che racchiude il gioco */
	float offset_finestra_width = window_width / 6.0; // Coordinata in basso a sinistra del game di gioco
	float offset_finestra_height = 0.0;

	Figura finestra_di_gioco;
	finestra_di_gioco.nTriangles = 2;
	finestra_di_gioco.position = vec3(offset_finestra_width, offset_finestra_height, 0.0);
	finestra_di_gioco.nome = FINESTRA;
	INIT_PIANO(&finestra_di_gioco, vec4(0.0, 0.0, 0.0, 0.0));
	finestra_di_gioco.Model = mat4(1.0);
	finestra_di_gioco.scale = vec3((float)window_width / 1.5, (float)window_height, 1.0);
	finestra_di_gioco.Model = scale(finestra_di_gioco.Model, finestra_di_gioco.scale);
	INIT_VAO(&finestra_di_gioco);
	Scena->push_back(finestra_di_gioco);

	/* Pacman */
	Figura pacman;
	pacman.nTriangles = 30;
	pacman.position = vec3((float)window_width / 4.0, (float)window_height / 20.0, 0.0);
	pacman.orientamento = DESTRA;
	pacman.nome = PACMAN;
	INIT_PACMAN(0.0, 0.0, 0.2, 0.2, &pacman, vec4(1.0, 1.0, 0.0, 1.0), vec4(1.0, 0.9, 0.0, 1.0));
	pacman.Model = mat4(1.0);
	pacman.scale = vec3(window_width / 12.0, window_width / 12.0, 0.0);
	pacman.Model = scale(pacman.Model, pacman.scale);
	INIT_VAO(&pacman);
	Scena->push_back(pacman);
}

/* Funzione che data una figura, un angolo di rotazione in gradi ricalcola la posizione, la scala e la rotazione della figura */
void posizionaOrientaScala(Figura* forma, float angoloLocal) {
	float angoloUsato = (angoloLocal < 0.0f) ? angolo : angoloLocal;
	forma->Model = mat4(1.0f);
	forma->Model = translate(forma->Model, vec3(forma->position.x + dx, forma->position.y + dy, 0.0f));
	forma->Model = rotate(forma->Model, radians(angoloUsato), vec3(0, 0, 1));
	forma->Model = scale(forma->Model, forma->scale);
}