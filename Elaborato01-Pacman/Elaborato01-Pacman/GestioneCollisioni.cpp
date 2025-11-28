#include "GestioneCollisioni.h"

/* Variabili esterne */
/* Scena */
extern vector<Figura> Scena;

/* Gioco */
extern int punteggio;			// Conteggio del punteggio del giocatore
extern int counterCibo;			// Conteggio del cibo ancora nella finestra di gioco

/* Animazione */
extern bool check_collisione;

/* Verifica se due oggetti di tipo Figura collidono utilizzando i loro Bounding Box nel sistema di riferimento del mondo.
    Parametri:
    - obj1: Prima figura da controllare per la collisione.
    - obj2: Seconda figura da controllare per la collisione.
     Restituisce:
    - true se i Bounding Box delle due figure si intersecano, false altrimenti
*/
bool checkCollision(Figura obj1, vec4 obj2) {

	/* Guarda le collisioni sull'asse x */
	bool collisionX = obj1.min_BB_w.x <= obj2.z && obj1.max_BB_w.x >= obj2.x;

	/* Guarda le collisioni sull'asse y */
	bool collisionY = obj1.min_BB_w.y <= obj2.w && obj1.max_BB_w.y >= obj2.y;

	/*Si ha collisione se c'è collisione sia nella direzione x che nella direzione y */
	return collisionX && collisionY;
}

/* Funzione per gestire le azioni da eseguire in base al tipo di figura con cui avviene */
void actionAfterCollision(Figura* fig) {
	if (fig->nome == FARFALLE && fig->isalive) {
		if (checkCollision(Scena[PACMAN], vec4(fig->min_BB_w.x, fig->min_BB_w.y, fig->max_BB_w.x, fig->max_BB_w.y))) {
			fig->isalive = false;
			punteggio += 50;
			counterCibo--;
		}
	}
	else if (fig->nome == CERCHI && fig->isalive) {
		if (checkCollision(Scena[PACMAN], vec4(fig->min_BB_w.x, fig->min_BB_w.y, fig->max_BB_w.x, fig->max_BB_w.y))) {
			fig->isalive = false;
			punteggio += 10;
			counterCibo--;
		}
	}
	else if (fig->nome == MURI && fig->isalive) {
		if (checkCollision(Scena[PACMAN], vec4(fig->min_BB_w.x, fig->min_BB_w.y, fig->max_BB_w.x, fig->max_BB_w.y))) {
			check_collisione = true;
		}
	}
}