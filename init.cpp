#include "init.h"
#include "game.h"

const float FPS = 30;

ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_EVENT e;
bool running = true;

unsigned int get_random_int(unsigned int min, unsigned int max) {

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

int init_all() {

    srand(time(NULL));

    if (!al_init()) {
        cout << "Failed to initialize Allegro." << endl;
        return -1;
    }

    if (!al_init_image_addon()) {
        cout << "Failed to initialize the image addon." << endl;
        return -1;
    }

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!display) {
        cout << "Failed to create the display." << endl;
        return -1;
    }

    if (!al_install_keyboard()) {
        cout << "Failed to install the keyboard." << endl;
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        cout << "Failed to create the event queue." << endl;
        al_destroy_display(display);
        return -1;
    }

    timer = al_create_timer(0.30 / FPS);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    return 0;

}

void register_all() {

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    al_register_event_source(event_queue, al_get_keyboard_event_source());

}

void destroy_all() {

    al_destroy_display(display);
    al_destroy_bitmap(player.bitmaps["UP"]);
    al_destroy_bitmap(player.bitmaps["LEFT"]);
    al_destroy_event_queue(event_queue);

}
