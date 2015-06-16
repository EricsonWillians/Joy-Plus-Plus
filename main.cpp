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
#include "objects.h"

// Example of external "plot" (Procedure),
// that's going to run inside Allegro's main-loop.

void event_plot()
{
    if (App::event_type() == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        App::shut_down();
    }
    if (App::event_type() == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (App::event().keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            App::shut_down();
        }
        if (App::event().keyboard.keycode == ALLEGRO_KEY_ENTER)
        {
            cout << "Bloody hell! This shit actually works! ";
        }
    }
}

void visual_plot()
{
    static Image x("sample.png");
    x.draw();
}

int main(int argc, char **argv)
{
    App app(800, 600);
    app.set_background_color(200, 0, 0);
    app.add_event_scene(Scene("Event Plot", event_plot));
    app.add_visual_scene(Scene("Visual Plot", visual_plot));
    app.run();
    return 0;
}

