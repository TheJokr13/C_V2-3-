#define MAX_ENEMI_COUNT 10


typedef struct ENEMI {
    Vec2 pos;
    Vec2 vel;
    COLOR color;
    int health;
    int ENABLED;
} ENEMI;

void init_ENEMI(ENEMI* ENEMIS, COLOR color, int ENABLED) {
    for (int i = 0; i < MAX_ENEMI_COUNT; i++) {
        ENEMIS[i] = (ENEMI){ (Vec2) { randominrange(0, SW-50), 
        randomfloatinrange(-SW, -50) }, (Vec2) 
        { 0.0, randomfloatinrange(2, 6) }, color, 3, ENABLED};
    }
}

Vec2 UPDATE_ENEMIS(ENEMI* ENEMIS, BULLET* BULLETS, 
PLAYER* PLAYERS, Vec2 score, Vec2* Hit_point) {
    for (int i = 0; i < MAX_ENEMI_COUNT; i++) {
        for (int j = 0; j < MAX_BULLET_COUNT; j++) {
            if (BULLETS[j].ENABLED == 0) continue;
            if (abs(ENEMIS[i].pos.x - BULLETS[j].pos.x) < 50 
            && abs(ENEMIS[i].pos.y - BULLETS[j].pos.y) < 50 ) {
                *Hit_point = (Vec2) {ENEMIS[i].pos.x + 22, ENEMIS[i].pos.y + 22};
                ENEMIS[i].pos = (Vec2) {randominrange(0, SW-50), 
                randomfloatinrange(-SW, -50)};
                BULLETS[j].ENABLED = 0;
                if (max(score.x, score.y)%10 == 0 
                && max(score.x, score.y) != 0) {
                    for (int k = 0; k < MAX_ENEMI_COUNT; k++) 
                    ENEMIS[k].vel.y += 2;
                }
                
                if (BULLETS[j].SHOOT_BY == 0) score.x+=1;
                if (BULLETS[j].SHOOT_BY == 1) score.y+=1;
                
                break;
            }
        }
        for (int j = 0; j < 2; j++) {
            if (abs(ENEMIS[i].pos.x - PLAYERS[j].pos.x) < 50 
            && abs(ENEMIS[i].pos.y - PLAYERS[j].pos.y) < 50 ) {
                *Hit_point = (Vec2) {ENEMIS[i].pos.x + 22,
                 ENEMIS[i].pos.y + 22};
                ENEMIS[i].pos = (Vec2) {randominrange(0, SW-50),
                 randomfloatinrange(-SW, -50)};
                PLAYERS[j].health -= 1;
                if (PLAYERS[j].health <= 0) {
                    PLAYERS[j].health = 3;
                    PLAYERS[j].pos = (Vec2) {SW/2, SH/1.5};
                }
            }
        }

        ENEMIS[i].pos.y += ENEMIS[i].vel.y;
        if (ENEMIS[i].pos.y > SH) ENEMIS[i].pos = (Vec2) 
        {randominrange(0, SW-50), randomfloatinrange(-SW, -50)};
    }
    return score;
}



void DRAW_ENEMIS(render_info* r_i, 
ENEMI* ENEMIS, debug_info* DEBUG_INFO) {
    SDL_Surface* playerSurface = IMG_Load("mob_1.png");
    if (!playerSurface) {
        printf("haha");
        return -1;
    }
    SDL_Texture* playerTexture = 
    SDL_CreateTextureFromSurface(r_i->renderer, playerSurface);

    SDL_SetTextureBlendMode(&playerTexture, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < MAX_ENEMI_COUNT; i++) {
        
        if (!playerTexture) {
            printf("Error creating texture: %s \n", SDL_GetError());
        }
        SDL_Rect playerRenderer = { ENEMIS[i].pos.x, ENEMIS[i].pos.y
        ,50, 50};
        SDL_RenderCopy(r_i->renderer, playerTexture, NULL, &playerRenderer);
    }
    SDL_DestroyTexture(playerTexture);
}