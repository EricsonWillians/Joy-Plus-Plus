#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define ACTOR_SIZE 32

typedef const char path;
unsigned int get_random_int(unsigned int min, unsigned int max);

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern bool running;
int init_all();
void register_all();
void destroy_all();

#endif // INIT_H_INCLUDED
