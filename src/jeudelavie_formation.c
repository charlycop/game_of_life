#include "../includes/jeudelavie_formation.h"

static bool ** allocate_formation(void){

    // Allocate memory for the array of rows
    bool ** formation = (bool **)malloc(NB_LIGNE * sizeof(bool *));
    
    if (formation == NULL){
        printf("Cannot malloc the formation 2D array !\n");
        exit;
    }
    
    // Allocate memory for each row
    for (uint16_t i = 0; i < NB_LIGNE; i++) {
        formation[i] = (bool *)malloc(NB_COL * sizeof(bool));
        
        if (formation == NULL){
            printf("Cannot malloc the formation 2D array on line %u !\n", i);
            exit;
        }
    }
    
    return formation;
}

static void deallocate_formation(bool*** formation){
    // Free the memory when you're done
    for (uint16_t i = 0; i < NB_LIGNE; i++) {
        free((*formation)[i]);
    }
    
    free(*formation), *formation = NULL;
}

void deinit_formations_buffers(bool*** formation, bool*** formation_buffer){
    deallocate_formation(formation);
    deallocate_formation(formation_buffer);
}

void init_formations_buffers(bool*** formation, bool*** formation_buffer){
    
    uint16_t i, j;
    static bool need_allocation = true;
    
    if (need_allocation){
        *formation        = allocate_formation();
        *formation_buffer = allocate_formation();
        need_allocation != need_allocation;
    }
  
    for (i = 0; i < NB_LIGNE; i++)
        for (j = 0; j < NB_COL; j++)
            (*formation)[i][j] = false;

    // Formation de démo au centre 
    (*formation)[GRID_HEIGHT/2-4][GRID_WIDTH/2+0] = true;
    (*formation)[GRID_HEIGHT/2-3][GRID_WIDTH/2+0] = true;
    (*formation)[GRID_HEIGHT/2-2][GRID_WIDTH/2+0] = true;
    (*formation)[GRID_HEIGHT/2-1][GRID_WIDTH/2+0] = true;
    (*formation)[GRID_HEIGHT/2-1][GRID_WIDTH/2-1] = true;
    (*formation)[GRID_HEIGHT/2-0][GRID_WIDTH/2+0] = true;
    (*formation)[GRID_HEIGHT/2+1][GRID_WIDTH/2+0] = true;
    (*formation)[GRID_HEIGHT/2+2][GRID_WIDTH/2+0] = true;
    (*formation)[GRID_HEIGHT/2+3][GRID_WIDTH/2+0] = true;
    (*formation)[GRID_HEIGHT/2+4][GRID_WIDTH/2+0] = true;

    copy_array(*formation, *formation_buffer);
}

void draw_formation(bool** formation, SDL_Renderer* renderer){
    SDL_Rect rect;
    uint16_t i, j;

    for (i = 0; i < NB_LIGNE; i++){
        for (j = 0; j < NB_COL; j++){
            DEFINE_RECT(i, j, rect);

            if (formation[i][j] == true)
                SDL_SetRenderDrawColor(renderer, COLOR_RED);
            else
                SDL_SetRenderDrawColor(renderer, COLOR_WHITE);

            SDL_RenderFillRect(renderer, &rect);
        }
    }
    
}


static uint8_t check_around(uint16_t i, uint16_t j, bool ** formation){
    uint8_t nb_voisins = 0;
    
    if (formation[i-1][j-1] == true) nb_voisins++;
    if (formation[i-1][j+0] == true) nb_voisins++;
    if (formation[i-1][j+1] == true) nb_voisins++;
    if (formation[i+0][j-1] == true) nb_voisins++;
    if (formation[i+0][j+1] == true) nb_voisins++;
    if (formation[i+1][j-1] == true) nb_voisins++;
    if (formation[i+1][j+0] == true) nb_voisins++;
    if (formation[i+1][j+1] == true) nb_voisins++;
    
    return nb_voisins;
}

uint16_t copy_array(bool** src, bool** tgt){
     uint16_t i, j;
     uint16_t diff = 0;
     
     for(i = 0; i < NB_LIGNE; i++)
        for(j = 0; j < NB_COL; j++){
            if (tgt[i][j] != src[i][j]){
                diff++;
                tgt[i][j] = src[i][j];
            }
        }
    
    return diff;
}

void prepare_next_formation(bool** formation, bool** formation_buffer){
    uint16_t i, j;
    uint8_t nb_voisins;

    for (i = 1; i < NB_LIGNE-1; i++){
        for (j = 1; j < NB_COL-1; j++){
            nb_voisins = check_around(i, j, formation);
            
            if(formation[i][j] == true){
                if (nb_voisins < 2 || nb_voisins > 3)
                    formation_buffer[i][j] = false;
            } else {
                if (nb_voisins == 3)
                    formation_buffer[i][j] = true;
            }
        }
    }

}


void toggle_square(Sint32 x, Sint32 y, bool** formation){
    
    uint16_t i, j;
    DEFINE_INDICES(x, y, i, j);

    formation[i][j] = !formation[i][j];

}

