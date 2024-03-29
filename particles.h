#pragma once
#define MAX_PARTICLE_COUNT 10000

typedef struct {COLOR* colors; int length;} GRADIENT;
typedef struct {COLOR color; Vec2 BASE_pos; Vec2 pos; Vec2 vel; float opacity;
 float MAX_life_time; float C_life_time; GRADIENT GRAD; int TYPE;
int LOOP; int ENABLED;} PARTICLE;


PARTICLE init_particle(COLOR color, Vec2 pos, Vec2 vel, float opacity,
 float MAX_life_time, float C_life_time, GRADIENT GRAD, int TYPE,
  int LOOP, int ENABLED) {
    PARTICLE _ = {.color = color, .BASE_pos = pos, .pos = pos, .vel = vel,
    .opacity = opacity, .MAX_life_time = MAX_life_time,
     .C_life_time = C_life_time, .GRAD = GRAD, .TYPE = TYPE,
      .LOOP = LOOP, .ENABLED = ENABLED};
    return _;
}



// Function to interpolate between two colors
COLOR lerp_color(COLOR color1, COLOR color2, float t) {
    COLOR result;
    result.r = (int)(color1.r * (1 - t) + color2.r * t);
    result.g = (int)(color1.g * (1 - t) + color2.g * t);
    result.b = (int)(color1.b * (1 - t) + color2.b * t);
    return result;
}



void UPDATE_PARTICLES(PARTICLE* PARTICLES,
 int PARTICLE_COUNT, render_info* r_i) {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        // PARTICLES[i].
        if (PARTICLES[i].C_life_time >= PARTICLES[i].MAX_life_time 
        || PARTICLES[i].ENABLED == 0) {
            if (PARTICLES[i].LOOP == 1) {
                PARTICLES[i].C_life_time = 1;
                PARTICLES[i].pos = PARTICLES[i].BASE_pos;
            } else {
                PARTICLES[i].C_life_time = 1;
                PARTICLES[i].ENABLED = 0;
                continue;
            }
        }
        PARTICLES[i].pos.x += PARTICLES[i].vel.x;
        PARTICLES[i].pos.y += PARTICLES[i].vel.y;
        PARTICLES[i].pos.y += sinf(PARTICLES[i].C_life_time);
        PARTICLES[i].pos.y += cosf(PARTICLES[i].C_life_time);


        if (PARTICLES[i].pos.y < 0) PARTICLES[i].vel.y *= -1;
        if (PARTICLES[i].pos.y + 5 > SH) PARTICLES[i].vel.y *= -1;
        PARTICLES[i].opacity = 
        255.0 - (255.0 * (PARTICLES[i].C_life_time/PARTICLES[i].MAX_life_time));

        float GRAD_lenght = PARTICLES[i].GRAD.length;

        int index = (int)
        round((PARTICLES[i].C_life_time/PARTICLES[i].MAX_life_time)
        *(GRAD_lenght));

        PARTICLES[i].color = PARTICLES[i].GRAD.colors[index];

        PARTICLES[i].C_life_time += 1;
        SDL_Rect sq = { PARTICLES[i].pos.x, PARTICLES[i].pos.y, 5, 5};

        SDL_SetRenderDrawColor(r_i->renderer, PARTICLES[i].color.r, 
        PARTICLES[i].color.g, PARTICLES[i].color.b, PARTICLES[i].opacity);
        SDL_RenderFillRect(r_i->renderer, &sq);
    }
}

void init_BLOW_EFFECT(PARTICLE* PARTICLES, int PARTICLE_COUNT, Vec2 position,
Vec2 velocity, int life_time, GRADIENT GRADIENTS,
int TYPE, int LOOP, int ENABLED) {
    int loop = 0;
    for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
        if (PARTICLES[i].ENABLED == 1) continue;
        if (loop >= PARTICLE_COUNT) break;
        float var_x = 0;
        float var_y = 0;
        var_x = randomfloatinrange(-abs(velocity.x), abs(velocity.x));
        var_y = randomfloatinrange(-abs(velocity.y), abs(velocity.y));

        // Initialize particle with varied velocity
        PARTICLES[i] = init_particle((COLOR) {0, 0, 0}, position,
        (Vec2) {var_x, var_y}, 255, life_time, 
        randominrange(0, life_time), GRADIENTS, TYPE, LOOP, ENABLED);
        loop += 1;
    }
}

void init_PICKUP_EFFECT(PARTICLE* PARTICLES, int PARTICLE_COUNT,
 Vec2 position, Vec2 velocity, int life_time, GRADIENT GRADIENTS,
  int TYPE, int LOOP, int ENABLED) {
    int loop = 0;
    for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
        if (PARTICLES[i].ENABLED == 1) continue;
        if (loop >= PARTICLE_COUNT) break;
        float var_x = 0;
        float var_y = 0;
        var_x = randomfloatinrange(-abs(velocity.x), abs(velocity.x));
        var_y = randomfloatinrange(-abs(velocity.y), abs(velocity.y));
        PARTICLES[i] = init_particle((COLOR) {0, 0, 0}, (Vec2) 
        {randominrange(position.x-abs(velocity.x*velocity.x),
        position.x+abs(velocity.x*velocity.x)),
        randominrange(position.y-abs(velocity.y*velocity.y),
        position.y+abs(velocity.y*velocity.y))},
        (Vec2) {var_x, var_y}, 255, life_time, randominrange(0, life_time),
        GRADIENTS, TYPE, LOOP, ENABLED);
        loop += 1;
    }
}

void init_FIRE_EFFECT(PARTICLE* PARTICLES, int PARTICLE_COUNT, Vec2 position,
Vec2 velocity, int life_time, GRADIENT GRADIENTS,
int TYPE, int LOOP, int ENABLED) {
    int loop = 0;
    for (int i = 0; i < MAX_PARTICLE_COUNT; i++) {
        if (PARTICLES[i].ENABLED == 1) continue;
        if (loop >= PARTICLE_COUNT) break;
        float var_x = 0;
        float var_y = 0;
        var_x = randomfloatinrange(-abs(velocity.x), abs(velocity.x));
        var_y = -abs(velocity.y);
        
        PARTICLES[i] = init_particle((COLOR) {0, 0, 0}, 
        (Vec2) {randominrange(position.x - (abs(velocity.x)*life_time/velocity.x),
        position.x + (abs(velocity.x)*life_time/velocity.x)), position.y},
        (Vec2) {var_x, var_y}, 
        255, life_time, randominrange(1, life_time), GRADIENTS, TYPE, LOOP, ENABLED);
        loop += 1;
    }
}



void init_PARTICLES(PARTICLE* PARTICLES, int PARTICLE_COUNT) {
    COLOR EMPTY_COLOR[1];
    EMPTY_COLOR[0] = (COLOR) {0, 0, 0};
    GRADIENT EMPTY_GRADIENTS;
    EMPTY_GRADIENTS.colors = EMPTY_COLOR;
    EMPTY_GRADIENTS.length = 6;
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        PARTICLES[i] = init_particle((COLOR) {0, 0, 0},
        (Vec2) {0.0, 0.0}, (Vec2) {0.0, 0.0}, 
        255, 1, 1, EMPTY_GRADIENTS, 0, 0, 0);
    }
}

void set_fire_gradient(COLOR* FIRE_COLORS) {
    FIRE_COLORS[0] = (COLOR) {255, 255, 255};
    FIRE_COLORS[1] = (COLOR) {246, 175, 95};
    FIRE_COLORS[2] = (COLOR) {225, 151, 36};
    FIRE_COLORS[3] = (COLOR) {246, 89, 48};
    FIRE_COLORS[4] = (COLOR) {246, 59, 9};
    FIRE_COLORS[5] = (COLOR) {156, 33, 0};
    FIRE_COLORS[6] = (COLOR) {78, 16, 0};
}