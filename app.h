#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#include <allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

typedef const char path;

class App
{
public:
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT e;
    bool running;
    const char *window_title;
    int screen_width;
    int screen_height;
    float FPS;

    App(int screen_width, int screen_height, const char *window_title = "Joy++ Application", float FPS = 30);
    int init_all();
    void register_all();
    void run();
    void destroy_all();

    void set_background_color(int r, int g, int b);
    unsigned int get_random_int(unsigned int min, unsigned int max);
};

#endif // APP_H_INCLUDED
