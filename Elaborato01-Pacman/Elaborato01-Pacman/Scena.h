#pragma once

#include "lib.h"
#include "ShaderMaker.h"
#include "Strutture.h"
#include "InitGeometrie.h"
#include "InitVAO.h"
#include "Muri.h"
#include "Cibo.h"

void costruisciScena(vector<Figura>* Scena);
void posizionaOrientaScala(Figura* forma, float angoloLocal = -1.0f);