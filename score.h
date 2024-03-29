#pragma once
#include "libs.h"
#include "render.h"


const TTF_Font* font;

typedef struct SCORE {
    int score;
    int player;
} SCORE;


TTF_Font* init_SCORE() {
    const char* fontPath = "light-arial.ttf";
    int size = 25;


    if (TTF_Init() == -1) {
        printf("Erreur lors de l'initialisation de SDL_ttf: %s\n",
        TTF_GetError());
    
    }
    font= TTF_OpenFont(fontPath, size);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police : %s\n",
        TTF_GetError());
    }
    return 0;
}




void DRAW_SCORE(Vec2 scores, render_info* r_i,
 TTF_Font* font, PLAYER* PLAYERS) {
    char buf[24];
    snprintf(buf, 24, "Player One Lives : %d",
    PLAYERS[0].health);
    renderText(r_i->renderer, font, buf, 20, 990, white);


    snprintf(buf, 24, "Player One Score : %d",
    (int)scores.x);
    renderText(r_i->renderer, font, buf, 420, 990, white);

    snprintf(buf, 24, "Level : %d",
    ((int)max(scores.x, scores.y)/10)+1);
    renderText(r_i->renderer, font, buf, 1660, 50, white);

    snprintf(buf, 24, "Player Two Lives : %d",
    PLAYERS[1].health);
    renderText(r_i->renderer, font, buf, 1620, 990, white);

    
    snprintf(buf, 24, "Player Two Score : %d",
    (int)scores.y);
    renderText(r_i->renderer, font, buf, 1220, 990, white);

}