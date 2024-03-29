#pragma once
#define FALSE 0
#define TRUE 1
#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct {int x; int y;} Vec2;
typedef struct { int r; int g; int b; } COLOR;
typedef struct { int vx; int vy; int px;
int py; int s; COLOR col; } CUBE;
typedef struct { int px; int py; int s_x;
 int sy; COLOR col; } SLIDER;


COLOR init_COLOR(int r, int g, int b) {
    COLOR color = { .r = r,.g = g,.b = b };
    return color;
}

CUBE init_CUBE(int vx, int vy, int px, int py, int s, COLOR col) {
    CUBE cube = { .vx = vx,.vy = vy,.px = px,.py = py,
    .s = s,.col = col };
    return cube;
}
void RV(CUBE* C) {
    int vx = randominrange(2, 5);
    int vy = randominrange(2, 5);
    vx = (randominrange(0, 1) == 0) ? vx : -vx;
    vy = (randominrange(0, 1) == 0) ? vy : -vy;
    C->vx = vx;
    C->vy = vy;
}

SLIDER init_SLIDER(int px, int py, int s_x, int sy, COLOR col) {
    SLIDER slider = { .px = px,.py = py,.s_x = s_x,
    .sy = sy,.col = col };
    return slider;
}

void DRAW_OBJS(CUBE* C, SLIDER* S, render_info* r_i) {
    SDL_Rect sq = { C[0].px,C[0].py,C[0].s,C[0].s };
    SDL_SetRenderDrawColor(r_i->renderer, C[0].col.r,
     C[0].col.g, C[0].col.b, 255);
    SDL_RenderFillRect(r_i->renderer, &sq);
    for (int i = 0; i < 3; i++) {
        SDL_Rect sq = { S[i].px,S[i].py,S[i].s_x,S[i].sy };
        SDL_SetRenderDrawColor(r_i->renderer, S[i].col.r,
         S[i].col.g, S[i].col.b, 255);
        SDL_RenderFillRect(r_i->renderer, &sq);
    }
}

TTF_Font* init_utilities() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("fonts/light-arial.ttf", 40);
    if (!font) {
        printf("Error loading font: %s \n", TTF_GetError());
        return 1;}
    return font;
}