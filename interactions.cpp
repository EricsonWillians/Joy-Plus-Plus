#include "interactions.h"

void kill_enemy() {
    for (int i = 0; i < player.cartridge.size(); i++) {
        for (int j = 0; j < enemies.size(); j++) {
            if (collide_with_bullet(&enemies[j], &player.cartridge[i])) {
                player.cartridge.erase(player.cartridge.begin() + i);
                enemies.erase(enemies.begin() + j);
                player.cartridge.push_back(create_bullet());
            }
        }
    }
}

void kill_player() {
    for (int i = 0; i < enemies.size(); i++) {
        if (collide_with_actor(&enemies[i], &player)) {
            scene = GAME_OVER;
        }
    }
}

void run_interactions() {
    kill_enemy();
    kill_player();
}
