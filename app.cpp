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

Scene::Scene(string scene_name, plot _plot)
{
    name = scene_name;
    p = _plot;
}

string Scene::get_name(void) { return name; }
plot Scene::get_plot(void) { return p; }
void Scene::set_name(string scene_name) { name = scene_name; }
void Scene::set_plot(plot _plot) { p = _plot; }

App::App(int screen_width, int screen_height, const char *window_title, float FPS)
{
    // Initializing non-static members.

    this->window_title = window_title;
    this->screen_width = screen_width;
    this->screen_height = screen_height;
    this->FPS = FPS;
    this->background_color = al_map_rgb(0, 0, 0);

    // Starting Allegro

    this->init_all();
    this->register_all();
}

// Initializing static members.

ALLEGRO_DISPLAY *App::display = nullptr;
ALLEGRO_EVENT_QUEUE *App::event_queue = nullptr;
ALLEGRO_TIMER *App::timer = nullptr;
ALLEGRO_EVENT App::e;
bool App::running = true;
bool App::redraw = true;
img_map App::images;

int App::init_all()
{
    // I'm developing on Windows 7, and MinGW does not handle
    // the new fancy alternative for randomness of C++11 properly.
    // So don't blame my oldschool approach, you Unix user.

    srand(time(nullptr));

    if (!al_init())
    {
        cout << "Failed to initialize Allegro." << endl;
        return -1;
    }

    if (!al_init_image_addon())
    {
        cout << "Failed to initialize the image addon." << endl;
        return -1;
    }

    this->display = al_create_display(this->screen_width, this->screen_height);

    if (!this->display)
    {
        cout << "Failed to create the display." << endl;
        return -1;
    }

    al_set_window_title(this->display, this->window_title);

    if (!al_install_keyboard())
    {
        cout << "Failed to install the keyboard." << endl;
        return -1;
    }

    this->event_queue = al_create_event_queue();

    if (!this->event_queue)
    {
        cout << "Failed to create the event queue." << endl;
        al_destroy_display(this->display);
        return -1;
    }

    this->timer = al_create_timer(0.30 / this->FPS);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    return 0;
}

void App::register_all()
{
    al_register_event_source(this->event_queue, al_get_display_event_source(this->display));
    al_register_event_source(this->event_queue, al_get_timer_event_source(this->timer));
    al_start_timer(this->timer);
    al_register_event_source(this->event_queue, al_get_keyboard_event_source());
}

void App::run()
{
    while (this->running)
    {
        this->redraw = false;
        while (!al_is_event_queue_empty(this->event_queue))
        {
            al_wait_for_event(this->event_queue, &this->e);
            if (this->e.type == ALLEGRO_EVENT_TIMER)
            {
                this->redraw = true;
            } else if (!this->event_scenes.empty())
            {
                for (auto const &it : this->event_scenes)
                {
                    it.second();
                }
            }
        }
        if (this->redraw)
        {
            if (!this->visual_scenes.empty())
            {
                for (auto const &it : this->visual_scenes)
                {
                    it.second();
                }
            }
            al_flip_display();
            al_clear_to_color(background_color);
        }
    }
    this->destroy_all();
}

void App::destroy_all()
{
    al_destroy_display(this->display);
    for (auto const &it : this->images)
    {
        al_destroy_bitmap(it.second);
    }
    al_destroy_event_queue(this->event_queue);
}

ALLEGRO_EVENT App::event() {
    return App::e;
}

ALLEGRO_EVENT_TYPE App::event_type() {
    return App::e.type;
}

void App::shut_down()
{
    App::running = false;
}

void App::add_event_scene(Scene scene)
{
    this->event_scenes[scene.get_name()] = scene.get_plot();
}

void App::add_visual_scene(Scene scene)
{
    this->visual_scenes[scene.get_name()] = scene.get_plot();
}

void App::set_background_color(int r, int g, int b)
{
    this->background_color = al_map_rgb(r, g, b);
}

unsigned int App::get_random_int(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}
