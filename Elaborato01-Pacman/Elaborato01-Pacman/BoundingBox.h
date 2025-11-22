#pragma once

#include "lib.h"
#include "Strutture.h"

void findBB(Figura* fig);
void disegnaFormaConBB(Figura& forma, bool wireframe = false, bool showBB = false);
void updateBB(Figura* fig);