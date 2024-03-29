typedef struct PLAYER {
    Vec2 pos;
    Vec2 vel;
    int health;
    int power_ups;
} PLAYER;

void init_PLAYERS(PLAYER* PLAYERS) {
    for (int i = 0; i < 3; i++) {
        PLAYERS[i] = (PLAYER){ (Vec2) { 0.0, 0.0 }, (Vec2) { 0.0, 0.0 }, 3, 0 };
    }
}

void UPDATE_PLAYERS(PLAYER* PLAYERS, CONTROLER* CONTROLERS) {
    for (int i = 0; i < 3; i++) {
        PLAYERS[i].pos.x += CONTROLERS[i].DIR.x;
        PLAYERS[i].pos.y += CONTROLERS[i].DIR.y;

        handle_collision_with_screen_bounds(&PLAYERS[i]);
    }
}

void handle_collision_with_screen_bounds(PLAYER* PLAYERS) {
    // Détection de la collision avec les bords gauche et droit de l'écran
    if (PLAYERS->pos.x < 0) {
        PLAYERS->pos.x = 0;
    } else if (PLAYERS->pos.x > SW - 50) { 
        PLAYERS->pos.x = SW - 50;
    }

    // Détection de la collision avec les bords haut et bas de l'écran
    if (PLAYERS->pos.y < 0) {
        PLAYERS->pos.y = 0;
    } else if (PLAYERS->pos.y > SH - 50) {
        PLAYERS->pos.y = SH - 50;
    }
}