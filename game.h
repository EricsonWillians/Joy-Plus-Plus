#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "init.h"

#define GAME 0
#define GAME_OVER 1

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define PLAYER_SPEED 4
#define PLAYER_AMMO 1
#define PLAYER_BULLET_SPEED 2
#define ENEMY_DISTANCE_FACTOR 768
#define ENEMY_DISTANCE_MULTIPLICATIVE_FACTOR 2

extern int scene;

ALLEGRO_BITMAP *load_bmp(path *s);

struct Bullet {
    int direction;
    int x;
    int y;
    int speed;
    bool alive;
};

Bullet create_bullet();

struct Actor {
    map<string, ALLEGRO_BITMAP*> bitmaps;
    int facing;
    bool shooting;
    int ammo;
    vector<Bullet> cartridge;
    int x;
    int y;
    int speed;
};

void init_game_bitmaps();
void draw_game_bitmaps();

extern map<string, bool> key_states;
void init_key_states();
void check_states(ALLEGRO_EVENT *e);

extern int raid;

void init_structs();
bool collide_with_actor(Actor *collider, Actor *collided);
bool collide_with_bullet(Actor *collider, Bullet *bullet);
void control_player(Actor *target, int speed);

extern struct Actor player;
extern void draw_player();

extern ALLEGRO_BITMAP *enemy_up;
extern ALLEGRO_BITMAP *enemy_left;
extern int initial_enemies;
extern int enemy_speed;
extern vector<Actor> enemies;
extern void draw_enemies();

#endif // GAME_H_INCLUDED
