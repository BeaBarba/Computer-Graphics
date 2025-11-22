#pragma once

#include "lib.h"

enum Forma {
    BACKGROUND = 0,
    FINESTRA = 1,
    PACMAN = 2,
    MURI = 3,
    FARFALLE = 4,
    CERCHI = 5,
    FANTASMI = 6
};

enum Orientamento {
    DESTRA = 0,
    SU = 1,
    SINISTRA = 2,
    GIU = 3
};

typedef struct {
    int nome;                       // Serve a definire il tipo di figura
    GLuint VAO;                     // Identificatore del Vertex Array Object (VAO)
    GLuint VBO_vertices;            // Identificatore del Vertex Buffer Object (VBO) che contiene le coordinate dei vertici dell'oggetto
    GLuint VBO_colors;              // Identificatore di un VBO che contiene i colori dei vertici dell'oggetto
    int nv;                         // Numero di vertici della figura geometrica
    int nTriangles;                 // Numero di triangoli che costituiscono l'oggetto
    vector<vec3> vertices;          // Vector che contiene le coordinate dei vertici dell'oggetto. Ogni elemento del vettore è un vec3, che rappresenta una posizione 3D (x, y, z)
    vector<vec4> colors;            // Vector che contiene i colori dei vertici dell'oggetto. Ogni elemento del vettore è un vec4, che rappresenta un colore RGBA (red, green, blue, alpha)
    int render;                     // Specifica come devono essere interpretati i vertici  nella fase di rendering
    mat4 Model;                     // Matrice di Modellazione associata alla figura che posizione l'oggetto nel mondo
    vec3 position;                  // Posizione in coordinate del mondo
    vec3 scale;                     // Scala
    Orientamento orientamento;      // Stabilisce in che direzione è girata la figura
} Figura;