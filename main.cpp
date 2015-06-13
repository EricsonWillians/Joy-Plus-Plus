#include "init.h"
#include "game.h"
#include "interactions.h"

int main(int argc, char **argv){

    init_all();
    register_all();
    init_key_states();
    init_structs();
    init_game_bitmaps();

    while (running) {

        bool redraw = false;
        while (!al_is_event_queue_empty(event_queue)) {

            ALLEGRO_EVENT e;
            al_wait_for_event(event_queue, &e);

            check_states(&e);
            control_player(&player, player.speed);

            if (e.type == ALLEGRO_EVENT_TIMER) {
                redraw = true;
            } else if (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                running = false;
            } else if (e.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (e.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    running = false;
                }
                if (e.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    cout << "It works!";
                }
            }
        }

        if (redraw) {
            if (scene == GAME) {
                draw_game_bitmaps();
                run_interactions();
            } else if (scene == GAME_OVER) {
                cout << "YOU'RE DEAD! ";
            }

            al_clear_to_color(al_map_rgb(0, 0, 0));
        }

    }

    destroy_all();

    return 0;
}
