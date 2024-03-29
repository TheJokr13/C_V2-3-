#define MAX_BULLET_COUNT 100

typedef struct BULLET {
    Vec2 pos;
    Vec2 vel;
    COLOR color;
    int opacity;
    int size;
    int SHOOT_BY;
    int ENABLED;
} BULLET;

BULLET init_bullet(Vec2 pos, Vec2 vel, int SHOOT_BY, int ENABLED) {
    return (BULLET) {pos, vel, (COLOR) 
    {255, 255, 255}, 255, 5, SHOOT_BY, ENABLED};
}

void init_bullets(BULLET* BULLETS) {
    for (int i = 0; i < MAX_BULLET_COUNT; i++) {
        BULLETS[i] = init_bullet((Vec2) {0.0, 0.0}, (Vec2) {0.0, 0.0}, 0, 0);
    }
}

void UPDATE_BULLETS(BULLET* BULLETS) {
    for (int i = 0; i < MAX_BULLET_COUNT; i++) {
        if (BULLETS[i].ENABLED == 0) continue;
        if (BULLETS[i].pos.x < 0 || BULLETS[i].pos.x > SW ||
         BULLETS[i].pos.y < 0 || BULLETS[i].pos.y > SH) BULLETS[i].ENABLED = 0;
        BULLETS[i].pos.x += BULLETS[i].vel.x;
        BULLETS[i].pos.y += BULLETS[i].vel.y;
    }
}

void DISPLAY_BULLETS(BULLET* BULLETS, int bullet_count, render_info* r_i) {
    for (int i = 0; i < bullet_count; i++) {
        if (BULLETS[i].ENABLED == 0) continue;
        SDL_Rect sq = {BULLETS[i].pos.x, BULLETS[i].pos.y,
         BULLETS[i].size, BULLETS[i].size};
        SDL_SetRenderDrawColor(r_i->renderer, BULLETS[i].color.r, 
        BULLETS[i].color.g, BULLETS[i].color.b, BULLETS[i].opacity);
        SDL_RenderFillRect(r_i->renderer, &sq);
    }
}

void FIRE_BULLET(BULLET* BULLETS, Vec2 pos, Vec2 vel, int SHOOT_BY) {
    // printf("Fire bullet\n");
    // printf("%d %d\n", pos.x, pos.y);
    int loop = 0;
    for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
        if (BULLETS[i].ENABLED == 1) continue;
        BULLETS[i] = init_bullet(pos, vel, SHOOT_BY, 1);
        break;
    }
}

void check_shoot(BULLET* BULLETS, PLAYER* PLAYERS, 
CONTROLER* CONTROLERS, PLAYERS_SHOOT_EVENT* PLAYERS_SHOOT_EVENT) {
    if (PLAYERS_SHOOT_EVENT->SHOOTING1) FIRE_BULLET(BULLETS, (Vec2) 
    {PLAYERS[0].pos.x + 22, PLAYERS[0].pos.y}, (Vec2) {0, -10}, 0);
    if (PLAYERS_SHOOT_EVENT->SHOOTING2) FIRE_BULLET(BULLETS, (Vec2) 
    {PLAYERS[1].pos.x + 22, PLAYERS[1].pos.y}, (Vec2) {0, -10}, 1);
}