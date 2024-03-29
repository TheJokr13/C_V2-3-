#pragma once

#include <SDL.h>
#include <SDL_TTF.h>
#include <SDL_IMAGE.h>


#define WS_UN SDL_WINDOWPOS_UNDEFINED
#define W_S SDL_WINDOW_SHOWN
#define R_P_S SDL_RENDERER_PRESENTVSYNC

//Taille de la fen�tre
#define SW 1920
#define SH 1080

SDL_Color white = { 255, 255, 255, 255 };
SDL_Color black = { 0, 0, 0, 255 };
SDL_Rect scoreZone = { 0, 980, SW, 100 };

typedef struct render_info {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int err;
} render_info;

typedef struct debug_info {
    int SHOW_HITBOX;
} debug_info;


render_info init_render_info(SDL_Window* window,
 SDL_Renderer* renderer, int err) {
    render_info renderInfo = { .window = window,
    .renderer = renderer,.err = err };
    return renderInfo;
}

render_info init_renderer() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n",
        SDL_GetError());
        return init_render_info(NULL, NULL, -1);
    }
    // Cr�ation de la fen�tre
    SDL_Window* window = SDL_CreateWindow("PONG !",
    WS_UN, WS_UN, SW, SH, W_S | R_P_S);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenètre : %s\n",
        SDL_GetError());
        SDL_Quit();
        return init_render_info(window, NULL, -1);
    }
    SDL_Renderer* renderer = 
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Pong\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return init_render_info(window, renderer, -1);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return init_render_info(window, renderer, 0);
}


// Function to load an image
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file) {
    SDL_Surface* surface = SDL_LoadBMP(file);
    if (surface == NULL) {
        // Handle error
        printf("Unable to load image %s! SDL_image Error: %s\n", file);
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", file);
    }
    //SDL_FreeSurface(surface);
    return texture;
}


void renderText(SDL_Renderer* renderer, TTF_Font* font,
const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}