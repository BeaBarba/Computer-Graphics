#pragma once

#include "lib.h"
#include "Strutture.h"

void INIT_PIANO(Figura* fig, vec4 color);
void INIT_PACMAN(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom);
void INIT_MURO(vec3 vs_bottom, vec3 vd_bottom, vec3 vs_top, vec3 vd_top, Figura* fig, vec4 color_top, vec4 color_bottom);
void INIT_BUTTERFLY(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom);
void INIT_CIRCLE(float cx, float cy, float raggiox, float raggioy, Figura* fig, vec4 color_top, vec4 color_bottom);
