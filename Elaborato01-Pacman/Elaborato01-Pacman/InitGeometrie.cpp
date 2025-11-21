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