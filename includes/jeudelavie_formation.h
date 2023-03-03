#ifndef JEUDELAVIE_FORMATION_H
#define JEUDELAVIE_FORMATION_H

#include <stdbool.h>
#include <stdint.h>
#include "stdio.h"
#include <stdlib.h> // malloc
#include <SDL.h>
#include "jeudelavie_common.h"

void deinit_formations_buffers(bool*** formation, bool*** formation_buffer);
void init_formations_buffers(bool*** formation, bool*** formation_buffer);
void draw_formation(bool** formation, SDL_Renderer* renderer);
uint16_t copy_array(bool** src, bool** tgt);
void prepare_next_formation(bool** formation, bool** formation_buffer);
void toggle_square(Sint32 x, Sint32 y, bool** formation);


#endif // JEUDELAVIE_FORMATION_H