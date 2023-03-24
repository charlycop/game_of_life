#ifndef JEUDELAVIE_PARAMS_H
#define JEUDELAVIE_PARAMS_H

#define GAME_NAME "Jeu de la vie"
#define IMAGES_PATH "img\\"

// SDL MACROS
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT  768
#define GRID_SIZE  10
#define GRID_WIDTH  SCREEN_WIDTH / GRID_SIZE
#define GRID_HEIGHT SCREEN_HEIGHT / GRID_SIZE
#define COLOR_RED   255, 0, 0, 255
#define COLOR_WHITE 255, 255, 255, 255
#define COLOR_BLACK 0, 0, 0, 255
#define DEFINE_RECT(line, col, var) \
                var.y = GRID_SIZE*line + 1; \
                var.x = GRID_SIZE*col + 1; \
                var.h = var.w = GRID_SIZE-1

#define DEFINE_INDICES(x, y, line, col) \
                line = y/GRID_SIZE; \
                col  = x/GRID_SIZE

// JEU DE LA VIE MACROS
#define NB_LIGNE GRID_HEIGHT
#define NB_COL   GRID_WIDTH

#endif //JEUDELAVIE_PARAMS_H