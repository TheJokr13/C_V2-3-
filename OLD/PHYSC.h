#pragma once
// #include "UTILS.h"
// #include "SCORE.h"

void UPDATE_TICK_SLIDERS(int* KEYS, SLIDER* SD) {
    if (KEYS[2] == 1)SD[0].py -= 4;
    if (KEYS[3] == 1)SD[0].py += 4;
    if (KEYS[0] == 1)SD[1].py -= 4;
    if (KEYS[1] == 1)SD[1].py += 4;
    for (int i = 0; i < 3; i++) {
        if (SD[i].py <= 0)SD[i].py = 0;
        if (SD[i].py + SD[i].sy >= SH)SD[i].py = SH - SD[i].sy;
    }
}

//Parametre avec les deux joueurs
int UPDATE_TICK_CUBE(CUBE* C, SLIDER* SD, SCORE *scoreP1, SCORE *scoreP2, int LAST_HITTED, PARTICLE *PARTICLES, int PARTICLE_COUNT, PARTICLE *PARTICLES_GOAL, int PARTICLE_COUNT_GOAL) {
    C[0].px += C[0].vx;
    C[0].py += C[0].vy;
    if (C[0].px + C[0].s >= SW || C[0].px <= 0) {
        C[0].vx *= -1;
        init_BLOW_EFFECT(PARTICLES_GOAL, PARTICLE_COUNT_GOAL, C[0], 60);
        //Si la balle touche a gauche de l'�cran increment score joueur 1 et sinon joueur
        if (C[0].px + C[0].s >= SW) scoreP1->score += 1;
        if (C[0].px <= 0) scoreP2->score += 1;
        C[0].vy = 0;
        C[0].px = SW / 2 - C[0].s;
        C[0].py = SH / 2 - C[0].s;
        RV(&C[0]);
        LAST_HITTED = -1;
    }
    if (C[0].py + C[0].s >= SH || C[0].py <= 0)C[0].vy *= -1;
    for (int j = 0; j < 2; j++) {
        if (C[0].px<SD[j].px + SD[j].s_x &&
            C[0].px + C[0].s>SD[j].px &&
            C[0].py<SD[j].py + SD[j].sy &&
            C[0].py + C[0].s>SD[j].py && j != LAST_HITTED) {
            LAST_HITTED = j;
            C[0].vx *= -1;
            C[0].vx += (C[0].vx > 0) ? 1 : -1;
            init_BLOW_EFFECT(PARTICLES, PARTICLE_COUNT, C[0], 30);
        }
    }
    return LAST_HITTED;
}