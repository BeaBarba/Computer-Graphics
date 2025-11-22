#include "InitGeometrie.h"

void INIT_PIANO(Figura* fig, vec4 color) {

    fig->vertices.clear();
    fig->colors.clear();

    /* Vertici */
    fig->vertices.push_back(vec3(0.0, 0.0, 0.0));   // Punto in basso a sinistra
    fig->vertices.push_back(vec3(1.0, 0.0, 0.0));   // Punto in basso a destra
    fig->vertices.push_back(vec3(1.0, 1.0, 0.0));   // Punto in alto a destra
    fig->vertices.push_back(vec3(0.0, 1.0, 0.0));   // Punto in alto a sinistra

    /* Colore */
    fig->colors.push_back(color);            // Colore vertice in basso a sinistra
    fig->colors.push_back(color);            // Colore vertice in basso a destra
    fig->colors.push_back(color);               // Colore vertice in alto a sinistra
    fig->colors.push_back(color);               // Colore vertice in alto a destra

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;
}

void INIT_PACMAN(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom) {
    int i;                                          // Contatore
    float t;                                        // Parametro del punto i-esmo sulla circonferenza
    float xx, yy;
    float stepA = (2 * PI) / fig->nTriangles;

    fig->vertices.clear();
    fig->colors.clear();

    fig->vertices.push_back(vec3(cx, cy, 0.0));     // Inserisco il vertice che è il centro della circonferenza
    fig->colors.push_back(color_top);

    for (i = 3; i < fig->nTriangles - 3; i++) {
        t = (double)i * stepA;
        xx = cx + raggiox * cos(t);
        yy = cy + raggioy * sin(t);

        fig->vertices.push_back(vec3(xx, yy, 0.0));
        fig->colors.push_back(color_bottom);
    }

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;
}

void INIT_MURO(vec3 vs_bottom, vec3 vd_bottom, vec3 vs_top, vec3 vd_top, Figura* fig, vec4 color_top, vec4 color_bottom) {

    fig->vertices.clear();
    fig->colors.clear();

    /* Vertici */
    fig->vertices.push_back(vs_bottom);     // Punto in basso a sinistra
    fig->vertices.push_back(vd_bottom);     // Punto in basso a destra
    fig->vertices.push_back(vd_top);        // Punto in alto a destra
    fig->vertices.push_back(vs_top);        // Punto in alto a sinistra

    /* Colore */
    fig->colors.push_back(color_bottom);    // Colore vertice in basso a sinistra
    fig->colors.push_back(color_bottom);    // Colore vertice in basso a destra
    fig->colors.push_back(color_top);       // Colore vertice in alto a destra
    fig->colors.push_back(color_top);       // Colore vertice in alto a sinistra

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;
}