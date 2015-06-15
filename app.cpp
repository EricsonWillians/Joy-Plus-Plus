#include "app.h"



App::App(int screen_width, int screen_height, const char *window_title, float FPS)
{
    this->window_title = window_title;
    this->screen_width = screen_width;
    this->screen_height = screen_height;
    this->FPS = FPS;
}

ALLEGRO_DISPLAY *App::display = nullptr;
ALLEGRO_EVENT_QUEUE *App::event_queue = nullptr;
ALLEGRO_TIMER *App::timer = nullptr;
ALLEGRO_EVENT App::e;
bool App::running = true;

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

    App::display = al_create_display(this->screen_width, this->screen_height);

    if (!App::display)
    {
        cout << "Failed to create the display." << endl;
        return -1;
    }

    al_set_window_title(App::display, this->window_title);

    if (!al_install_keyboard())
    {
        cout << "Failed to install the keyboard." << endl;
        return -1;
    }

    App::event_queue = al_create_event_queue();

    if (!App::event_queue)
    {
        cout << "Failed to create the event queue." << endl;
        al_destroy_display(App::display);
        return -1;
    }

    App::timer = al_create_timer(0.30 / App::FPS);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    return 0;
}

void App::register_all()
{
    al_register_event_source(App::event_queue, al_get_display_event_source(App::display));
    al_register_event_source(App::event_queue, al_get_timer_event_source(App::timer));
    al_start_timer(App::timer);
    al_register_event_source(App::event_queue, al_get_keyboard_event_source());
}

void App::run()
{
    this->init_all();
    this->register_all();

    while (App::running)
    {
        // Run the plots.

        if (!this->scenes.empty())
        {
            for (auto const &it : this->scenes)
            {
                it.second();
            }
        }
    }

    this->destroy_all();
}

void App::destroy_all()
{
    al_destroy_display(this->display);
    /*
    al_destroy_bitmap(player.bitmaps["UP"]);
    al_destroy_bitmap(player.bitmaps["LEFT"]);
    */
    al_destroy_event_queue(this->event_queue);
}

void App::add_scene(Scene scene)
{
    this->scenes[scene.get_name()] = scene.get_plot();
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
