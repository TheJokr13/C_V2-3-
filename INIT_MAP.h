#pragma once



void init_MAP(CUBE* CUBE, SLIDER* SLIDERS) {
    int vec_x = randominrange(2, 5);
    int vec_y = randominrange(2, 5);
    vec_x = (randominrange(0, 1) == 0) ? vec_x : -vec_x;
    vec_y = (randominrange(0, 1) == 0) ? vec_y : -vec_y;
    CUBE[0] = init_CUBE(vec_x, vec_y, SW / 2 - 10, SH / 2 - 10, 20, init_COLOR(255, 255, 255));
    SLIDERS[0] = init_SLIDER(50 - 10, SH / 2 - 50, 20, 100, init_COLOR(255, 255, 255));
    SLIDERS[1] = init_SLIDER(SW - 50 - 10, SH / 2 - 50, 20, 100, init_COLOR(255, 255, 255));
}