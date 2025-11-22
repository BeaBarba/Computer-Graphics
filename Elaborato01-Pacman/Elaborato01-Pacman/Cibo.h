#pragma once

#include "lib.h"
#include "Strutture.h"
#include "CampoDaGioco.h"

extern int campo[height_matrice][width_matrice];

struct Cibo {
	int row_start;
	int row_end;
	int column_start;
	int column_end;
};

struct CiboCoord {
	float centro_x;
	float centro_y;
	float raggio;
};

vector<Cibo> checkCiboInMatrice(int tipo_cibo);
vector<CiboCoord> calcolaCoordinateFarfalle(vector<vec3> vertices);
