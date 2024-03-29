typedef struct PLAYER {
    Vec2 pos;
    Vec2 vel;
    COLOR color;
    int health;
    int power_ups;
    int ENABLED;
} PLAYER;

void init_PLAYERS(PLAYER* PLAYERS, int ENABLED) {
    for (int i = 0; i < 2; i++) {
        PLAYERS[i] = (PLAYER){ (Vec2) {SW/2, SH/1.5}, 
        (Vec2) { 0.0, 0.0 }, (COLOR){0,0,0}, 3, 0, ENABLED};
    }
}

void UPDATE_PLAYERS(PLAYER* PLAYERS, CONTROLER* CONTROLERS) {
    for (int i = 0; i < 2; i++) {
        PLAYERS[i].pos.x += CONTROLERS[i].DIR.x;
        PLAYERS[i].pos.y += CONTROLERS[i].DIR.y;

        handle_collision_with_screen_bounds(&PLAYERS[i]);
    }
}

void handle_collision_with_screen_bounds(PLAYER* PLAYERS) {
    if (PLAYERS->pos.x < 0) {
        PLAYERS->pos.x = 0;
    } else if (PLAYERS->pos.x > SW - 50) { 
        PLAYERS->pos.x = SW - 50;
    }

    if (PLAYERS->pos.y < 0) {
        PLAYERS->pos.y = 0;
    } else if (PLAYERS->pos.y > SH - 50) {
        PLAYERS->pos.y = SH - 50;
    }
}

void DRAW_PLAYERS(render_info* r_i, PLAYER* PLAYERS, debug_info* DEBUG_INFO) {
    SDL_Surface* playerSurface = IMG_Load("player.png");
    if (!playerSurface) {
        printf("haha");
        return -1;
    }
    SDL_Texture* playerTexture = 
    SDL_CreateTextureFromSurface(r_i->renderer, playerSurface);

    SDL_SetTextureBlendMode(&playerTexture, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < 2; i++) {
        
        if (!playerTexture) {
        printf("Error creating texture: %s \n", SDL_GetError());}
        SDL_Rect playerRenderer = { PLAYERS[i].pos.x, PLAYERS[i].pos.y
        ,50, 50};
        SDL_RenderCopy(r_i->renderer, playerTexture, NULL, &playerRenderer);
    }
    SDL_DestroyTexture(playerTexture);
    
}

