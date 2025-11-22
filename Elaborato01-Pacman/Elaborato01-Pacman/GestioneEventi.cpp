#include "GestioneEventi.h"

/* Variabili Da Importare */
/* Finestra */
extern int window_width, window_height;			                            // Risoluzione finesta iniziale 
extern float window_width_update, window_height_update;                     // Risoluzione finestra di gioco aggiornata
extern float window_width_background, window_height_background;             // Risoluzione finestra 

/* Scena E Matrici Di Trasformazione */
extern vector<Figura> Scena;                                                // Lista che contiene le figure da disegnare
extern mat4 projection, projection_background;				                // Matrice che normalizza le coordinate del mondo in cordinate NDC

/* Aspect Razio */
float x_offset = 0.0, y_offset = 0.0;                                       // Offset per centrare la viewport

/* Funzione di callback chiamata ogni volta che la finestra(framebuffer) viene ridimensionata.
   Gestisce il corretto rapporto di aspetto e centra la viewport rispetto alle dimensioni della finestra.*/
void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    /* Prevenzione di divisione per zero */
    if (h == 0) h = 1;

    /* Aggiorna la matrice di proiezione ortografica in base alle dimensioni del mondo virtuale */
    projection = ortho(0.0f, (float)window_width, 0.0f, (float)window_height);
    projection_background = ortho(0.0f, (float)w, 0.0f, (float)h);

    /* Aggiorna la dimensione dello sfondo in base alla grandezza della finestra */
    window_width_background = w;
    window_height_background = h;

    // Calcola il rapporto di aspetto del “mondo”  
    float aspect_ratio_mondo = (float)window_width / (float)window_height;

    // Adatta la viewport a seconda del rapporto tra il mondo e la finestra
    if (aspect_ratio_mondo > (float)w / (float)h)
    {
        // Il mondo è relativamente più largo della finestra.
        // La larghezza della viewport è quella della finestra, l’altezza viene ridotta.
        window_width_update = (float)w;
        window_height_update = w / aspect_ratio_mondo;
        // Calcola l’offset verticale per centrare la viewport nel framebuffer più alto
        y_offset = ((float)h - window_height_update) / 2.0f;
        x_offset = 0.0;
    }
    else
    {
        // Il mondo è relativamente più stretto o alto della finestra.
        // L’altezza della viewport è quella della finestra, la larghezza viene ridotta.
        window_height_update = (float)h;
        window_width_update = h * aspect_ratio_mondo;
        // Calcola l’offset orizzontale per centrare la viewport nel framebuffer più largo
        x_offset = ((float)w - window_width_update) / 2.0f;
        y_offset = 0.0;
    }

    /* Imposta la viewport OpenGL con offset e dimensioni calcolate per centrarla e mantenere il giusto aspect ratio*/
    //glViewport(x_offset, y_offset, window_width_update, window_height_update);
}