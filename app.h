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
    int screen_width;
    int screen_height;
    float FPS;

    App(int screen_width, int screen_height, float FPS = 30);
    int init_all();
    void register_all();
    void destroy_all();
    unsigned int get_random_int(unsigned int min, unsigned int max);
};

#endif // APP_H_INCLUDED
