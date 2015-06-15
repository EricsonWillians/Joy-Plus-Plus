/*

Joy++ - A general-purpose multimedia engine.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

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
