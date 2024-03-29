#pragma once
#include <SDL_mixer.h>
#include <SDL_audio.h>
#define FILENAME "C:/Users/ldelphin/Desktop/C_V2/music.wav"




void audio_callback(void *userdata, Uint8 *stream, int len) {
    SDL_RWops *rw = (SDL_RWops *)userdata;
    SDL_RWread(rw, stream, 1, len);
}

int play_sound(){
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_AudioSpec spec;
    SDL_RWops *rw;
    if (!SDL_LoadWAV(FILENAME, &spec, &rw, NULL)) {
        printf("Could not load audio file %s! SDL_Error: %s\n", FILENAME, SDL_GetError());
        SDL_Quit();
        return -1;
    }

    spec.callback = audio_callback;
    spec.userdata = rw;

    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
    if (device == 0) {
        printf("Failed to open audio device! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeWAV(rw);
        SDL_Quit();
        return -1;
    }

    SDL_PauseAudioDevice(device, 0);

    printf("Press any key to quit...\n");
    getchar();

    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(rw);
    SDL_Quit();

    return 0;
}

// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
