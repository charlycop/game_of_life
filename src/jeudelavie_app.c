#include "../includes/jeudelavie_app.h"

static void init_SDL(SDL_Renderer** renderer_ptr, SDL_Window** window_ptr){
    uint16_t i;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    *window_ptr   = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window_ptr) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        exit(1);
    }

    *renderer_ptr = SDL_CreateRenderer(*window_ptr, -1, SDL_RENDERER_ACCELERATED);

    if (!*renderer_ptr) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        exit(1);
    }   

    SDL_SetRenderDrawColor(*renderer_ptr, COLOR_WHITE);
    SDL_RenderClear(*renderer_ptr);

    SDL_SetRenderDrawColor(*renderer_ptr, COLOR_BLACK);
    for (i = 0; i <= GRID_WIDTH; i++) {
        SDL_RenderDrawLine(*renderer_ptr, i * GRID_SIZE, 0, i * GRID_SIZE, SCREEN_HEIGHT);
    }
    for (i = 0; i <= GRID_HEIGHT; i++) {
        SDL_RenderDrawLine(*renderer_ptr, 0, i * GRID_SIZE, SCREEN_WIDTH, i * GRID_SIZE);
    }
}


void init_app(Jeudelavie_s* myGame){
    init_SDL(&myGame->renderer, &myGame->window);
    init_formations_buffers(&myGame->formation, &myGame->formation_buffer);
    init_buttons(myGame->renderer, &myGame->buttons);
    myGame->proceed_move = false;
    myGame->request_update = true;
    myGame->new_cycle = true;
}

void deinit_app(Jeudelavie_s* myGame){
    deinit_formations_buffers(&myGame->formation, &myGame->formation_buffer);
    deinit_buttons(&myGame->buttons);
    SDL_DestroyRenderer(myGame->renderer);
    SDL_DestroyWindow(myGame->window);
    SDL_Quit();
}

void start_button_handler(Jeudelavie_s* myGame){

    if(myGame->new_cycle){
        copy_array(myGame->formation, myGame->formation_buffer);
        myGame->new_cycle = false;
    }

    prepare_next_formation(myGame->formation, myGame->formation_buffer);
    
    if(copy_array(myGame->formation_buffer, myGame->formation) == 0){
        myGame->proceed_move = false;
        myGame->new_cycle = true;
    }
}


static Etat check_events(Jeudelavie_s* myGame){
    Etat next_state = STATE_CHECK_EVENT;

    while (SDL_PollEvent(&myGame->event)) {
        
        switch (myGame->event.type) {

            case SDL_QUIT:
                return STATE_DEINIT;
                break;

            case SDL_MOUSEBUTTONDOWN:
                // Check for left mouse button click
                if (myGame->event.button.button == SDL_BUTTON_LEFT) {
                    if (myGame->event.button.x >= myGame->buttons.button_coords_size[start].x &&
                        myGame->event.button.y >= myGame->buttons.button_coords_size[start].y &&
                        myGame->event.button.x <= myGame->buttons.button_coords_size[start].x + myGame->buttons.button_coords_size[start].w &&
                        myGame->event.button.y <= myGame->buttons.button_coords_size[start].y + myGame->buttons.button_coords_size[start].h)
                        {
                            myGame->proceed_move = !myGame->proceed_move;
                    }
                    else if (
                        myGame->event.button.x >= myGame->buttons.button_coords_size[clear].x &&
                        myGame->event.button.y >= myGame->buttons.button_coords_size[clear].y &&
                        myGame->event.button.x <= myGame->buttons.button_coords_size[clear].x + myGame->buttons.button_coords_size[clear].w &&
                        myGame->event.button.y <= myGame->buttons.button_coords_size[clear].y + myGame->buttons.button_coords_size[clear].h)
                        {
                            init_formations_buffers(&myGame->formation, &myGame->formation_buffer);
                            myGame->request_update = true;
                            myGame->new_cycle = true;
                    }
                    else {
                            toggle_square(myGame->event.button.x, myGame->event.button.y, myGame->formation);
                            myGame->request_update = true;
                            
                    }
                }
                break;
            default:
                break;
        }
    }

    if(myGame->proceed_move || myGame->request_update)
        next_state = STATE_PREPARE_DISPLAY;

    return next_state;
}

static void prepare_display(Jeudelavie_s* myGame){
     
    // Show formation
    draw_formation(myGame->formation, myGame->renderer);
    
    // Prepare buttons and new formation
    if (myGame->proceed_move){
        start_button_handler(myGame);
        SDL_RenderCopy(myGame->renderer, myGame->buttons.button_textures[stop], NULL, &myGame->buttons.button_coords_size[stop]);
    }
    else{
        SDL_RenderCopy(myGame->renderer, myGame->buttons.button_textures[start], NULL, &myGame->buttons.button_coords_size[start]);
    }

    SDL_RenderCopy(myGame->renderer, myGame->buttons.button_textures[clear], NULL, &myGame->buttons.button_coords_size[clear]);
}

static void display(Jeudelavie_s* myGame){
    // Update the screen
    SDL_RenderPresent(myGame->renderer);
    SDL_Delay(100);
}

// State Machine
void state_machine(Jeudelavie_s* myGame) {

    // Boucle principale de la machine à état
    while (myGame->actual_state != STATE_EXIT) {
        switch (myGame->actual_state) {
            case STATE_INIT:
                init_app(myGame);
                myGame->next_state = STATE_PREPARE_DISPLAY;
                break;

            case STATE_PREPARE_DISPLAY:
                prepare_display(myGame);
                myGame->next_state = STATE_DISPLAY;
                break;

            case STATE_DISPLAY:
                display(myGame);
                myGame->next_state = STATE_CHECK_EVENT;
                break;

            case STATE_CHECK_EVENT:
                myGame->next_state = check_events(myGame);
                break;
            
            case STATE_DEINIT:
                deinit_app(myGame);
                myGame->next_state = STATE_EXIT;
                break;

            default: // Allows to init when the states are not initialize at start
                myGame->next_state = STATE_INIT;
                break;
            
        }

        myGame->actual_state = myGame->next_state;
    }

}