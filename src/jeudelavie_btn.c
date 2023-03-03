#include "../includes/jeudelavie_btn.h"

void init_buttons(SDL_Renderer* renderer, buttons_s* buttons){

    // Load button image from BMP file
    SDL_Surface* button_surface = SDL_LoadBMP(IMAGES_PATH "button_start.bmp");
    if (!button_surface) {
        fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }

    buttons->button_textures[start] = SDL_CreateTextureFromSurface(renderer, button_surface);
    
    button_surface = SDL_LoadBMP(IMAGES_PATH "button_stop.bmp");
    if (!button_surface) {
        fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }

    buttons->button_textures[stop] = SDL_CreateTextureFromSurface(renderer, button_surface);
    
    button_surface = SDL_LoadBMP(IMAGES_PATH "button_clear.bmp");
    if (!button_surface) {
        fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }

    buttons->button_textures[clear] = SDL_CreateTextureFromSurface(renderer, button_surface);
    
    SDL_FreeSurface(button_surface);

    // Get button texture size
    int button_width, button_height;
    SDL_QueryTexture(buttons->button_textures[start], NULL, NULL, &button_width, &button_height);

    // Set button position and size
    buttons->button_coords_size[start].x = buttons->button_coords_size[stop].x = SCREEN_WIDTH - button_width;
    buttons->button_coords_size[clear].x = 0;
    buttons->button_coords_size[start].y = buttons->button_coords_size[stop].y = buttons->button_coords_size[clear].y = SCREEN_HEIGHT - button_height;
    buttons->button_coords_size[start].w = buttons->button_coords_size[stop].w = buttons->button_coords_size[clear].w = button_width;
    buttons->button_coords_size[start].h = buttons->button_coords_size[stop].h = buttons->button_coords_size[clear].h = button_height;

}

void deinit_buttons(buttons_s* buttons){
    free(buttons->button_textures[start]);
    free(buttons->button_textures[stop]);
    free(buttons->button_textures[clear]);
}