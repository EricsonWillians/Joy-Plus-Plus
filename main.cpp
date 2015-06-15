#include "app.h"

// Example of external "plot" (Procedure),
// that's going to run inside Allegro's main-loop.

void flow_plot()
{
    bool redraw = false;
    while (!al_is_event_queue_empty(App::event_queue))
    {

        al_wait_for_event(App::event_queue, &App::e);

        if (App::e.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        } else if (App::e.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            App::running = false;
        } else if (App::e.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (App::e.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                App::running = false;
            }
            if (App::e.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                cout << "It works!";
            }
        }
    }
    if (redraw)
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }
}

int main(int argc, char **argv)
{

    App app(800, 600);
    app.add_scene(Scene("Flow Plot", flow_plot));
    app.run();

    return 0;
}
