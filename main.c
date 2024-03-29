#define SDL_MAIN_HANDLED
#define FRAMERATE 1000/60
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "render.h"


float randomfloatinrange(float min, float max) {
    return min + (float)(rand()) * (float)(max - min) / RAND_MAX;
}
int randominrange(int min, int max) {return(rand() % (max-min+1))+min;}

#define PLAYER_SPEED 5

#include "utils.h"
#include "particles.h"
#include "controller.h"
#include "player.h"
#include "score.h"
#include "BULLET.h"
#include "enemi.h"

void destroy(render_info* r_i, TTF_Font* font) {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(r_i->renderer);
    SDL_DestroyWindow(r_i->window);
    TTF_Quit();
    SDL_Quit();
}
void Main_loop(render_info render_info, debug_info DEBUG_INFO, CONTROLER* CONTROLERS, BULLET* BULLETS, PLAYER* PLAYERS, PARTICLE* PARTICLES, ENEMI* ENEMIS, Vec2 scores, 
SDL_Texture* BACKGROUNDTexture, SDL_Rect BACKGROUNDRenderer, GRADIENT FIRE_GRADIENTS) {
    SDL_Event event;
    while (1) {
        PLAYERS_SHOOT_EVENT PLAYERS_SHOOT_EVENT;
        int events_info = handle_events(&render_info, CONTROLERS, 
        &PLAYERS_SHOOT_EVENT, &DEBUG_INFO);
        check_shoot(BULLETS, PLAYERS, CONTROLERS, &PLAYERS_SHOOT_EVENT);
        if (events_info != 0)return events_info;
        UPDATE_PLAYERS(PLAYERS, CONTROLERS);
        SDL_SetRenderDrawColor(render_info.renderer, 0, 0, 0, 255);
        SDL_RenderClear(render_info.renderer);
        SDL_RenderCopy(render_info.renderer, BACKGROUNDTexture, NULL, &BACKGROUNDRenderer);
        DRAW_PLAYERS(&render_info, PLAYERS, &DEBUG_INFO);
        UPDATE_PARTICLES(&PARTICLES, MAX_PARTICLE_COUNT, &render_info);
        DISPLAY_BULLETS(&BULLETS, MAX_BULLET_COUNT, &render_info);
        UPDATE_BULLETS(&BULLETS);
        DRAW_ENEMIS(&render_info, ENEMIS, &DEBUG_INFO);
        Vec2 Hit_POINT = (Vec2) {0, 0};
        scores = UPDATE_ENEMIS(ENEMIS, BULLETS, PLAYERS, scores, &Hit_POINT);
        if (Hit_POINT.x != 0 && Hit_POINT.y != 0) {
            init_BLOW_EFFECT(PARTICLES, 60, Hit_POINT, 
            (Vec2) {4.0, 4.0}, 30, FIRE_GRADIENTS, 1, 0, TRUE);}
        DRAW_SCORE(scores, &render_info, font, PLAYERS);
        SDL_RenderPresent(render_info.renderer); 
        SDL_Delay(FRAMERATE);}
}
int main(int argc, char* argv[]) {
    TTF_Font* font = init_utilities(font);
    render_info render_info = init_renderer();
    if (render_info.err != 0) return render_info.err;
    int LAST_HITTED = -1;
    PARTICLE PARTICLES[MAX_PARTICLE_COUNT];
    init_PARTICLES(PARTICLES, MAX_PARTICLE_COUNT);
    BULLET BULLETS[MAX_BULLET_COUNT];init_bullets(BULLETS);
    ENEMI ENEMIS[MAX_ENEMI_COUNT];init_ENEMI(ENEMIS, (COLOR) {0, 255, 0}, 1);
    CONTROLER CONTROLERS[2];init_CONTROLERS(CONTROLERS);
    PLAYER PLAYERS[2];init_PLAYERS(PLAYERS, 0);
    Vec2 scores = (Vec2) {0, 0};
    debug_info DEBUG_INFO = (debug_info) {0};
    COLOR FIRE_COLORS[6];
    set_fire_gradient(FIRE_COLORS);
    GRADIENT FIRE_GRADIENTS;
    FIRE_GRADIENTS.colors = FIRE_COLORS;
    FIRE_GRADIENTS.length = 6;
    for (int i = 50; i < SW; i+=100) {
        init_FIRE_EFFECT(PARTICLES, 60, (Vec2) {i, SH}, 
        (Vec2) {1.0, 1.0}, 60, FIRE_GRADIENTS, 3, 1, TRUE);}
    SDL_Surface* BACKGROUNDSurface = IMG_Load("back.png");
    if (!BACKGROUNDSurface) {printf("haha");
        return -1;}
    SDL_Texture* BACKGROUNDTexture = 
    SDL_CreateTextureFromSurface(render_info.renderer,BACKGROUNDSurface);
    if (!BACKGROUNDTexture) printf("Err texture: %s\n",SDL_GetError());
    SDL_Rect BACKGROUNDRenderer = {0, 0, SW, SH};
    
    Main_loop(render_info, DEBUG_INFO, CONTROLERS, BULLETS, PLAYERS, PARTICLES, ENEMIS, scores, BACKGROUNDTexture, BACKGROUNDRenderer, FIRE_GRADIENTS);
    SDL_DestroyTexture(BACKGROUNDTexture);
    destroy(&render_info, font);
    return 0;}
