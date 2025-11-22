#pragma once

#include "lib.h"
#include "Strutture.h"
#include "CampoDaGioco.h"

struct Muro {
    int riga_start = -1;
    int riga_end = -1;
    int colonna_start = -1;
    int colonna_end = -1;
};

struct MuroCoord {
    vec3 bottom_start = vec3(0.0, 0.0, 0.0);
    vec3 bottom_end = vec3(0.0, 0.0, 0.0);
    vec3 top_start = vec3(0.0, 0.0, 0.0);
    vec3 top_end = vec3(0.0, 0.0, 0.0);
};

//void costruisciMuri(vector<vec3> vertices);
vector<Muro> trasformaMatriceInMuri();
vector<MuroCoord> creaMuri(vector<vec3> vertices);