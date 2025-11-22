#include "BoundingBox.h"

/* Cerca le coordinate del Bounding Box */
void findBB(Figura* fig) {
    int n;
    n = fig->vertices.size();
    float minx = fig->vertices[0].x; // Assumiamo che il primo elemento sia il minimo iniziale
    float miny = fig->vertices[0].y; // Assumiamo che il primo elemento sia il minimo iniziale

    float maxx = fig->vertices[0].x; // Assumiamo che il primo elemento sia il massimo iniziale
    float maxy = fig->vertices[0].y; // Assumiamo che il primo elemento sia il massimo iniziale

    for (int i = 1; i < n; i++) {
        if (fig->vertices[i].x < minx) {
            minx = fig->vertices[i].x;
        }
        if (fig->vertices[i].x > maxx) {
            maxx = fig->vertices[i].x;
        }

        if (fig->vertices[i].y < miny) {
            miny = fig->vertices[i].y;
        }

        if (fig->vertices[i].y > maxy) {
            maxy = fig->vertices[i].y;
        }
    }

    fig->min_BB_obj = vec4(minx, miny, 0.0, 1.0);
    fig->max_BB_obj = vec4(maxx, maxy, 0.0, 1.0);
}

// Funzione per disegnare una forma grafica con la possibilità di visualizzare la bounding box (BB)
// Parametri:
// - forma: riferimento a un oggetto Figura che contiene dati della forma da disegnare
// - wireframe: opzione booleana per disegnare la forma in modalità wireframe (solo i contorni) oppure riempita (default: false)
// - showBB: opzione booleana per visualizzare la bounding box della forma come un poligono a 4 lati (default: false)
void disegnaFormaConBB(Figura& forma, bool wireframe, bool showBB) {
    //cout << "\n\ndentro forma bb " << endl;
    // Se wireframe è true, imposta la modalità di disegno in modo che tutte le facce siano solo contorni
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        // Altrimenti, riempi le facce in modalità solida
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Associa il Vertex Array Object (VAO) della forma, che contiene i dati dei vertici da disegnare
    glBindVertexArray(forma.VAO);
    
    // Disegna i vertici della forma come specificato da forma.render,
    // a partire dal primo vertice (0), per (forma.nv - 4) vertici in totale
    // La sottrazione di 4 è per escludere i vertici della bounding box
    glDrawArrays(forma.render, 0, forma.nv - 4);
    
    if (showBB) {
        // Se showBB è true, disegna la bounding box con una line loop collegando gli ultimi 4 vertici
        glDrawArrays(GL_LINE_LOOP, forma.nv - 4, 4);
    }

}

// Aggiorna le coordinate del Bounding Box di una figura nel sistema di riferimento del mondo,
// applicando la matrice di modellazione alle coordinate locali.
// Parametri:
//   - fig: Puntatore alla struttura Figura il cui Bounding Box deve essere aggiornato.
void updateBB(Figura* fig) {
    /* Trasforma direttamente le coordinate del Bounding Box locale nel sistema del mondo.Nella CPU in modo da gestire le collisioni
    fig->min_BB_w = fig->Model * fig->min_BB_obj;
    fig->max_BB_w = fig->Model * fig->max_BB_obj;
    */

    // 1. Definisci i 4 vertici d'angolo della BB locale (2D)
    vec4 v1 = vec4(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0, 1.0);
    vec4 v2 = vec4(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0, 1.0);
    vec4 v3 = vec4(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0, 1.0);
    vec4 v4 = vec4(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0, 1.0);

    // 2. Trasforma tutti i vertici nel sistema di coordinate del mondo
    vec4 t1 = fig->Model * v1;
    vec4 t2 = fig->Model * v2;
    vec4 t3 = fig->Model * v3;
    vec4 t4 = fig->Model * v4;

    // 3. Trova i veri min/max assoluti (AABB)
    float minX = std::min(t1.x, std::min(t2.x, std::min(t3.x, t4.x)));
    float maxX = std::max(t1.x, std::max(t2.x, std::max(t3.x, t4.x)));
    float minY = std::min(t1.y, std::min(t2.y, std::min(t3.y, t4.y)));
    float maxY = std::max(t1.y, std::max(t2.y, std::max(t3.y, t4.y)));

    // 4. Aggiorna la Bounding Box del mondo (usa vec4 per consistenza con fig->Model)
    fig->min_BB_w = vec4(minX, minY, 0.0, 1.0);
    fig->max_BB_w = vec4(maxX, maxY, 0.0, 1.0);
}