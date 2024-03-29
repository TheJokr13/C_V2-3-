typedef struct CONTROLER {
    Vec2 DIR;
    int main;
    int special;
} CONTROLER;

void init_CONTROLERS(CONTROLER* CTRL) {
    for (int i = 0; i < 3; i++) {
        CTRL[i] = (CONTROLER) {(Vec2) {0.0, 0.0}, FALSE, FALSE};
    }
}

int handle_events(render_info* render_info, CONTROLER* CONTROLERS) {
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
            if (event.key.keysym.sym == SDLK_z)CONTROLERS[1].DIR.y = -1;
            if (event.key.keysym.sym == SDLK_s)CONTROLERS[1].DIR.y = 1;
            if (event.key.keysym.sym == SDLK_q)CONTROLERS[1].DIR.x = 1;
            if (event.key.keysym.sym == SDLK_d)CONTROLERS[1].DIR.x = -1;
            if (event.key.keysym.sym == SDLK_UP)CONTROLERS[0].DIR.y = -1;
            if (event.key.keysym.sym == SDLK_DOWN)CONTROLERS[0].DIR.y = 1;
            if (event.key.keysym.sym == SDLK_LEFT)CONTROLERS[0].DIR.x = 1;
            if (event.key.keysym.sym == SDLK_RIGHT)CONTROLERS[0].DIR.x = -1;
            if (event.key.keysym.sym == SDLK_SPACE) {
                FIRE_BULLET()
            }
            if (event.key.keysym.sym == SDLK_CTRL)CONTROLERS[1].DIR.x = -1;

        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_z)CONTROLERS[1].DIR.y = 0;
            if (event.key.keysym.sym == SDLK_s)CONTROLERS[1].DIR.y = 0;
            if (event.key.keysym.sym == SDLK_q)CONTROLERS[1].DIR.x = 0;
            if (event.key.keysym.sym == SDLK_d)CONTROLERS[1].DIR.x = 0;
            if (event.key.keysym.sym == SDLK_UP)CONTROLERS[0].DIR.y = 0;
            if (event.key.keysym.sym == SDLK_DOWN)CONTROLERS[0].DIR.y = 0;
            if (event.key.keysym.sym == SDLK_LEFT)CONTROLERS[0].DIR.x = 0;
            if (event.key.keysym.sym == SDLK_RIGHT)CONTROLERS[0].DIR.x = 0;
        }
    }
    return 0;
}