#include "game.h"
#include "interactions.h"

int scene = GAME;

ALLEGRO_BITMAP *load_bmp(path *s) {
    ALLEGRO_BITMAP *bmp = nullptr;
    bmp = al_load_bitmap(s);
    if (!bmp) {

        al_show_native_message_box(display,
            "Fatal Error!",
            "Failed to load: " ,
            s,
            NULL,
            ALLEGRO_MESSAGEBOX_ERROR);

        al_destroy_display(display);
        return nullptr;

    }

    return bmp;
}

map<string, bool> key_states;
void init_key_states() {
    key_states["UP"] = false;
    key_states["DOWN"] = false;
    key_states["LEFT"] = false;
    key_states["RIGHT"] = false;
    key_states["W"] = false;
    key_states["S"] = false;
    key_states["A"] = false;
    key_states["D"] = false;
    key_states["LSHIFT"] = false;
    key_states["SPACE"] = false;
}

void set_state(ALLEGRO_EVENT *e, int al_key, string key_name, bool state) {
    for (auto it = key_states.begin(); it != key_states.end(); ++it) {
        if (e->keyboard.keycode == al_key) {
            if (it->first == key_name) {
                it->second = state;
            }
        }
    }
}
void check_states(ALLEGRO_EVENT *e) {
    if (e->type == ALLEGRO_EVENT_KEY_DOWN) {
        set_state(&(*e), ALLEGRO_KEY_UP, "UP", true);
        set_state(&(*e), ALLEGRO_KEY_DOWN, "DOWN", true);
        set_state(&(*e), ALLEGRO_KEY_LEFT, "LEFT", true);
        set_state(&(*e), ALLEGRO_KEY_RIGHT, "RIGHT", true);
        set_state(&(*e), ALLEGRO_KEY_W, "W", true);
        set_state(&(*e), ALLEGRO_KEY_S, "S", true);
        set_state(&(*e), ALLEGRO_KEY_A, "A", true);
        set_state(&(*e), ALLEGRO_KEY_D, "D", true);
        set_state(&(*e), ALLEGRO_KEY_LSHIFT, "LSHIFT", true);
        set_state(&(*e), ALLEGRO_KEY_SPACE, "SPACE", true);
    } else if (e->type == ALLEGRO_EVENT_KEY_UP) {
        set_state(&(*e), ALLEGRO_KEY_UP, "UP", false);
        set_state(&(*e), ALLEGRO_KEY_DOWN, "DOWN", false);
        set_state(&(*e), ALLEGRO_KEY_LEFT, "LEFT", false);
        set_state(&(*e), ALLEGRO_KEY_RIGHT, "RIGHT", false);
        set_state(&(*e), ALLEGRO_KEY_W, "W", false);
        set_state(&(*e), ALLEGRO_KEY_S, "S", false);
        set_state(&(*e), ALLEGRO_KEY_A, "A", false);
        set_state(&(*e), ALLEGRO_KEY_D, "D", false);
        set_state(&(*e), ALLEGRO_KEY_LSHIFT, "LSHIFT", false);
        set_state(&(*e), ALLEGRO_KEY_SPACE, "SPACE", false);
    }
}

int raid = 0;

void randomize_enemy_positions(Actor *a) {
    if (a->facing == UP) {
        a->x = get_random_int(0, SCREEN_WIDTH);
        a->y = get_random_int(SCREEN_HEIGHT, SCREEN_HEIGHT +
            get_random_int(0, ENEMY_DISTANCE_FACTOR *
                get_random_int(0, ENEMY_DISTANCE_MULTIPLICATIVE_FACTOR)));
    } else if (a->facing == DOWN) {
        a->x = get_random_int(0, SCREEN_WIDTH);
        a->y = get_random_int(-(SCREEN_HEIGHT +
            get_random_int(0, ENEMY_DISTANCE_FACTOR *
                get_random_int(0, ENEMY_DISTANCE_MULTIPLICATIVE_FACTOR))), 0);
    } else if (a->facing == LEFT) {
        a->x = get_random_int(SCREEN_WIDTH, SCREEN_WIDTH +
            get_random_int(0, ENEMY_DISTANCE_FACTOR *
                get_random_int(0, ENEMY_DISTANCE_MULTIPLICATIVE_FACTOR)));
        a->y = get_random_int(0, SCREEN_HEIGHT);
    } else if (a->facing == RIGHT) {
        a->x = get_random_int(-(SCREEN_WIDTH +
            get_random_int(0, ENEMY_DISTANCE_FACTOR *
                get_random_int(0, ENEMY_DISTANCE_MULTIPLICATIVE_FACTOR))), 0);
        a->y = get_random_int(0, SCREEN_HEIGHT);
    }
}

void generate_enemies(int q, int speed) {
    for (int i = 0; i < q; i++) {
        Actor a;
        a.facing = get_random_int(0, 3);
        a.speed = speed;
        randomize_enemy_positions(&a);
        enemies.push_back(a);
    }
}

Bullet create_bullet() {
    Bullet b;
    b.speed = PLAYER_BULLET_SPEED;
    b.alive = false;
    return b;
}

struct Actor player;
void draw_player() {
    if (player.facing == UP) {
        al_draw_bitmap(player.bitmaps["UP"], player.x, player.y, 0);
    }
    if (player.facing == DOWN) {
        al_draw_bitmap(player.bitmaps["UP"], player.x, player.y, ALLEGRO_FLIP_VERTICAL);
    }
    if (player.facing == LEFT) {
        al_draw_bitmap(player.bitmaps["LEFT"], player.x, player.y, 0);
    }
    if (player.facing == RIGHT) {
        al_draw_bitmap(player.bitmaps["LEFT"], player.x, player.y, ALLEGRO_FLIP_HORIZONTAL);
    }
}

vector<Actor> enemies;
void draw_enemies() {
    for (auto &enemy : enemies) {
        if (enemy.facing == UP) {
            enemy.y -= enemy.speed;
            al_draw_bitmap(enemy_up, enemy.x, enemy.y, ALLEGRO_FLIP_VERTICAL);
            if (enemy.y < -ACTOR_SIZE) {
                randomize_enemy_positions(&enemy);
            }
        } else if (enemy.facing == DOWN) {
            enemy.y += enemy.speed;
            al_draw_bitmap(enemy_up, enemy.x, enemy.y, 0);
            if (enemy.y > SCREEN_HEIGHT + ACTOR_SIZE) {
                randomize_enemy_positions(&enemy);
            }
        } else if (enemy.facing == LEFT) {
            enemy.x -= enemy.speed;
            al_draw_bitmap(enemy_left, enemy.x, enemy.y, ALLEGRO_FLIP_HORIZONTAL);
            if (enemy.x < -ACTOR_SIZE) {
                randomize_enemy_positions(&enemy);
            }
        } else if (enemy.facing == RIGHT) {
            enemy.x += enemy.speed;
            al_draw_bitmap(enemy_left, enemy.x, enemy.y, 0);
            if (enemy.x > SCREEN_WIDTH + ACTOR_SIZE) {
                randomize_enemy_positions(&enemy);
            }
        }
    //    cout << enemy.y << "|" << enemy.x << endl;
    }
}

void init_structs() {

    // Player

    player.bitmaps["UP"], player.bitmaps["LEFT"], player.bitmaps["FIRE"] = nullptr;
    player.shooting = false;
    player.ammo = PLAYER_AMMO;
    player.cartridge = vector<Bullet>();
    for (int i = 0; i < player.ammo; i++) {
        player.cartridge.push_back(Bullet());
        player.cartridge[i].speed = PLAYER_BULLET_SPEED;
        player.cartridge[i].alive = false;
    }
    player.x = (SCREEN_WIDTH / 2) - (ACTOR_SIZE / 2);
    player.y = (SCREEN_HEIGHT / 2) - (ACTOR_SIZE / 2);
    player.speed = PLAYER_SPEED;

    // Enemies

    int initial_enemies = 10;
    int enemy_speed = 4;
    generate_enemies(initial_enemies, enemy_speed);

}

bool collide_with_actor(Actor *collider, Actor *collided) {
    if (   (((collider->x + ACTOR_SIZE) > collided->x) && (collider->x < (collided->x + ACTOR_SIZE)))
        && (((collider->y + ACTOR_SIZE) > collided->y) && (collider->y < (collided->y + ACTOR_SIZE)))) {
        return true;
    } else {
        return false;
    }
}

bool collide_with_bullet(Actor *collider, Bullet *bullet) {
    if (   (((collider->x + ACTOR_SIZE) > bullet->x) && (collider->x < (bullet->x + ACTOR_SIZE)))
        && (((collider->y + ACTOR_SIZE) > bullet->y) && (collider->y < (bullet->y + ACTOR_SIZE)))) {
        return true;
    } else {
        return false;
    }
}

ALLEGRO_BITMAP *enemy_up = nullptr;
ALLEGRO_BITMAP *enemy_left = nullptr;
void init_game_bitmaps() {
   player.bitmaps["UP"] = load_bmp("GFX\\player_up.png");
   player.bitmaps["LEFT"] = load_bmp("GFX\\player_left.png");
   player.bitmaps["FIRE"] = load_bmp("GFX\\fire.png");
   enemy_up = load_bmp("GFX\\enemy_up.png");
   enemy_left = load_bmp("GFX\\enemy_left.png");
}

void control_player(Actor *target, int speed) {
    if (key_states["UP"] || key_states["W"]) {
        target->y -= speed;
        target->facing = UP;
    }
    if (key_states["DOWN"] || key_states["S"]) {
        target->y += speed;
        target->facing = DOWN;
    }
    if (key_states["LEFT"] || key_states["A"]) {
        target->x -= speed;
        target->facing = LEFT;
    }
    if (key_states["RIGHT"] || key_states["D"]) {
        target->x += speed;
        target->facing = RIGHT;
    }
    if (key_states["LSHIFT"]) {
        target->speed = PLAYER_SPEED * 2;
    } else if (!key_states["LSHIFT"]) {
        target->speed = PLAYER_SPEED;
    }
    if (key_states["SPACE"]) {
        for (auto &b : target->cartridge) {
            if (!b.alive) {
                b.direction = target->facing;
                b.alive = true;
                b.x = target->x;
                b.y = target->y;
            }
        }
    }
}

void draw_game_bitmaps() {

    draw_player();

    // The shooting.

    int distance = 0;
    for (auto &b : player.cartridge) {
        if (distance == b.speed * player.ammo) {
            distance = b.speed;
        }
        distance += b.speed;
        if (b.alive) {
            if (b.direction == UP) {
                b.y -= b.speed + distance;
                if (b.y < -ACTOR_SIZE) {
                    b.alive = false;
                }
            } else if (b.direction == DOWN) {
                b.y += b.speed + distance;
                if (b.y > SCREEN_HEIGHT + ACTOR_SIZE) {
                    b.alive = false;
                }
            } else if (b.direction == LEFT) {
                b.x -= b.speed + distance;
                if (b.x < -ACTOR_SIZE) {
                    b.alive = false;
                }
            } else if (b.direction == RIGHT) {
                b.x += b.speed + distance;
                if (b.x > SCREEN_WIDTH + ACTOR_SIZE) {
                    b.alive = false;
                }
            }
            al_draw_bitmap(player.bitmaps["FIRE"], b.x, b.y, 0);
        }
    }

    draw_enemies();
    al_flip_display();
}
