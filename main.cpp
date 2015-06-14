#include "app.h"

int main(int argc, char **argv)
{
    App app(800, 600);

    while (app.running)
    {
        bool redraw = false;
        while (!al_is_event_queue_empty(app.event_queue))
        {
            ALLEGRO_EVENT e;
            al_wait_for_event(app.event_queue, &e);

            if (e.type == ALLEGRO_EVENT_TIMER)
            {
                redraw = true;
            } else if (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                app.running = false;
            } else if (e.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (e.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    app.running = false;
                }
                if (e.keyboard.keycode == ALLEGRO_KEY_ENTER)
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

    app.destroy_all();

    return 0;
}
