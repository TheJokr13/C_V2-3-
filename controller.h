

typedef struct CONTROLER {
    Vec2 DIR;
    int main;
    int special;
    int SHOW_HITBOX;
} CONTROLER;

void init_CONTROLERS(CONTROLER* CTRL) {
    for (int i = 0; i < 3; i++) {
        CTRL[i] = (CONTROLER){ (Vec2) { 0.0, 0.0 }, FALSE, FALSE, FALSE };
    }
}


typedef struct {
    int x;
    int y;
    int width;
    int height;
    int speed;
    int ENABLED;
} Player;

Player initPlayer(int x, int y, int width, int height, int ENABLED) {
    Player player;
    player.x = x;
    player.y = y;
    player.width = width;
    player.height = height;
    player.speed = PLAYER_SPEED;
    player.ENABLED = ENABLED;

    return player;
}


typedef struct PLAYERS_SHOOT_EVENT {
    int SHOOTING1;
    int SHOOTING2;
} PLAYERS_SHOOT_EVENT;


int handle_events(render_info* render_info, CONTROLER* CONTROLERS, 
PLAYERS_SHOOT_EVENT* PLAYERS_SHOOT_EVENT, debug_info* DEBUG_INFO) {
    PLAYERS_SHOOT_EVENT->SHOOTING1 = 0;
    PLAYERS_SHOOT_EVENT->SHOOTING2 = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            // Fermeture de la fen�tre et de la SDL
            SDL_DestroyRenderer(render_info->renderer);
            SDL_DestroyWindow(render_info->window);
            SDL_Quit();
            return 1;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_z)
            CONTROLERS[1].DIR.y = -1 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_s)
            CONTROLERS[1].DIR.y = 1 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_q)
            CONTROLERS[1].DIR.x = -1 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_d)
            CONTROLERS[1].DIR.x = 1 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_UP)
            CONTROLERS[0].DIR.y = -1 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_DOWN)
            CONTROLERS[0].DIR.y = 1 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_LEFT)
            CONTROLERS[0].DIR.x = -1 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_RIGHT)
            CONTROLERS[0].DIR.x = 1 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_p) 
            DEBUG_INFO->SHOW_HITBOX = 1;
            if (event.key.keysym.sym == SDLK_SPACE) 
            PLAYERS_SHOOT_EVENT->SHOOTING2 = 1;
            if (event.key.keysym.sym == SDLK_0) 
            PLAYERS_SHOOT_EVENT->SHOOTING1 = 1;
            
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_z)
            CONTROLERS[1].DIR.y = 0 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_s)
            CONTROLERS[1].DIR.y = 0 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_q)
            CONTROLERS[1].DIR.x = 0 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_d)
            CONTROLERS[1].DIR.x = 0 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_UP)
            CONTROLERS[0].DIR.y = 0 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_DOWN)
            CONTROLERS[0].DIR.y = 0 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_LEFT)
            CONTROLERS[0].DIR.x = 0 * PLAYER_SPEED;
            if (event.key.keysym.sym == SDLK_RIGHT)
            CONTROLERS[0].DIR.x = 0 * PLAYER_SPEED;
        }
    }
    return 0;
}