/*

####################################################################

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

####################################################################

*/

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

/*

####################################################################

Member declarations follow this order:

1. Static Field Variables.
2. Non-static Field Variables.
3. Static Methods.
4. Constructors.
5. Destructor.
6. Non-static methods.
7. Accessors.
8. Mutators.

The order applies individually for each access specifier.
Be sure to follow it!

####################################################################

*/

using namespace std;
typedef const char *path;
typedef ALLEGRO_BITMAP *img;
typedef map<string, bool> key_map;
typedef void(*plot)();
typedef map<string, plot> act;

class Object

/*

####################################################################

The Object class is the super-class of all objects.

####################################################################

*/

{
protected:
    long int id;
public:
    Object(void);
    ~Object(void) {};
    long int get_id(void);
};

typedef map<long int, Object*> obj_map;

class Scene
{
private:
    string name;
    plot p;
public:
    Scene(string name, plot p);
    ~Scene(void) {};
    string get_name(void);
    plot get_plot(void);
    void set_name(string value);
    void set_plot(plot value);
};

class App

/*

####################################################################

The App class is responsible for abstracting the Allegro 5 initiali-
zation, as well as the main-loop and other core multimedia concepts.

Implementation Notes:

Everything in this class must be public!
Each member must be accessible to the user and the engine.

####################################################################

*/

{
public:
    static ALLEGRO_DISPLAY *display;
    static ALLEGRO_EVENT_QUEUE *event_queue;
    static ALLEGRO_TIMER *timer;
    static ALLEGRO_EVENT e;
    static bool running;
    static bool redraw;
    static key_map key_states;
    static obj_map objects;
    static long int object_counter;
    const char *window_title;
    int screen_width;
    int screen_height;
    float FPS;
    act event_scenes;
    act visual_scenes;
    ALLEGRO_COLOR background_color;

    static ALLEGRO_EVENT event();
    static ALLEGRO_EVENT_TYPE event_type();
    static void shut_down();

    App(int screen_width, int screen_height, const char *window_title = "Joy++ Application", float FPS = 30);
    ~App(void) {};

    int init_all(void);
    void register_all(void);
    void check_key_states(void);
    void init_key_states(void);
    void run(void);
    void destroy_all(void);
    void add_event_scene(Scene scene);
    void add_visual_scene(Scene scene);
    void remove_event_scene(Scene scene);
    void remove_visual_scene(Scene scene);

    long int get_object_count(void);
    unsigned int get_random_int(unsigned int min, unsigned int max);
    void set_key_state(int al_key, string key_name, bool state);
    void set_background_color(int r, int g, int b);
};

#endif // APP_H_INCLUDED
