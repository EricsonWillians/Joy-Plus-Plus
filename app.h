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

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

typedef const char *path;
typedef ALLEGRO_BITMAP *img;
typedef void(*plot)();
typedef map<string, plot> act;

class Scene
{
private:
    string name;
    plot p;
public:
    Scene(string name, plot p);
    ~Scene() {};
    string get_name();
    plot get_plot();
    void set_name(string value);
    void set_plot(plot value);
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
    ~App() {};
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
