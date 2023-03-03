#ifndef JEUDELAVIE_BTN_H
#define JEUDELAVIE_BTN_H

#define NB_BUTTONS 3

#include <SDL.h>
#include "stdio.h"
#include "jeudelavie_common.h"

typedef enum buttons_e{
    start,
    stop,
    clear
}buttons_e;

typedef struct buttons_s{
    SDL_Texture* button_textures[NB_BUTTONS];
    SDL_Rect     button_coords_size[NB_BUTTONS];
}buttons_s;

void init_buttons(SDL_Renderer* renderer, buttons_s* buttons);
void deinit_buttons(buttons_s* buttons);

#endif // JEUDELAVIE_BTN_H