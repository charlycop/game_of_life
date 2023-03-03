#ifndef JEUDELAVIE_APP_H
#define JEUDELAVIE_APP_H

#include <SDL.h>
#include "jeudelavie_common.h"
#include "jeudelavie_btn.h"
#include "jeudelavie_formation.h"

// Defines states
typedef enum {
    STATE_INIT,
    STATE_DISPLAY,
    STATE_CHECK_EVENT,
    STATE_PREPARE_DISPLAY,
    STATE_DEINIT,
    STATE_EXIT
} Etat;

typedef struct Jeudelavie{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    bool** formation;
    bool** formation_buffer;
    buttons_s buttons;      // contains the buttons structures
    bool proceed_move;      // to know that the user is watching the formation evolving
    bool request_update;    // to update the screen after the user added/removed a square
    Etat actual_state;      // for the FSM
    Etat next_state;        // for the FSM 
    bool new_cycle;
}Jeudelavie_s;


void init_app(Jeudelavie_s* myGame);
void deinit_app(Jeudelavie_s* myGame);
void start_button_handler(Jeudelavie_s* myGame);
void state_machine(Jeudelavie_s* myGame);

#endif // JEUDELAVIE_APP_H