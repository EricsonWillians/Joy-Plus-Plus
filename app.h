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
typedef void(*plot)();
typedef map<string, plot> act;

class Scene
{
private:
    string name;
    plot p;
public:
    Scene(string name, plot p)
    {
        this->name = name;
        this->p = p;
    }
    string get_name() { return this->name; }
    plot get_plot() { return this->p; }
    void set_name(string value) { this->name = value; }
    void set_plot(plot value) { this->p = value; }
};

class App
{
public:
    static ALLEGRO_DISPLAY *display;
    static ALLEGRO_EVENT_QUEUE *event_queue;
    static ALLEGRO_TIMER *timer;
    static ALLEGRO_EVENT e;
    static bool running;
    const char *window_title;
    int screen_width;
    int screen_height;
    float FPS;
    act scenes;
    act event_scenes;


    App(int screen_width, int screen_height, const char *window_title = "Joy++ Application", float FPS = 30);
    int init_all();
    void register_all();
    void run();
    void destroy_all();

    void add_scene(Scene scene);
    void remove_scene(Scene scene);
    void set_background_color(int r, int g, int b);
    unsigned int get_random_int(unsigned int min, unsigned int max);
};

#endif // APP_H_INCLUDED
