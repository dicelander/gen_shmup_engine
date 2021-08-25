//
//  collision.c
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 23/08/21.
//

#include <collision.h>
#include "../inc/collision.h"

struct COL_Generic {
    fix16 pos_x;
    fix16 pos_y;
    fix16 offset_x;
    fix16 offset_y;
    fix16 width;
    fix16 height;
};

bool collideENPlayer(Enemy* enemy, Player* player) {
    return (enemy->pos_x + enemy->offset_x < player->pos_x + player->offset_x + player->width && enemy->pos_x + enemy->offset_x + enemy->width > player->pos_x + player->offset_x && enemy->pos_y + enemy->offset_y < player->pos_y + player->offset_y + player->height && enemy->pos_y + enemy->offset_y + enemy->height >= player->pos_y + player->offset_y);
};

bool collideENShotPlayer(En_Shot* shot, Player* player) {
    return ((shot->pos_x + shot->offset_x) < ((player->pos_x + player->offset_x) + player->width) && ((shot->pos_x + shot->offset_x) + shot->width) > (player->pos_x + player->offset_x) && (shot->pos_y + shot->offset_y) < ((player->pos_y + player->offset_y) + player->height) && ((shot->pos_y + shot->offset_y) + shot->height) >= (player->pos_y + player->offset_y));
};

bool collidePLShotEnemy(Pl_Shot* shot, Enemy* enemy) {
    return (shot->pos_x + shot->offset_x < enemy->pos_x + enemy->offset_x + enemy->width && shot->pos_x + shot->offset_x + shot->width > enemy->pos_x + enemy->offset_x && shot->pos_y + shot->offset_y < enemy->pos_y + enemy->offset_y + enemy->height && shot->pos_y + shot->offset_y + shot->height >= enemy->pos_y + enemy->offset_y);
};

//bool collideGeneric(void* gen1, void* gen2) { //HIGHLY dependant on ordering inside the struct, be careful.
//    struct Col_Generic *a = (struct Col_Generic *) gen1;
//    struct Col_Generic *b = (struct Col_Generic *) gen2;
//    return (a->pos_x + a->offset_x < b->pos_x + b->offset_x + b->width && a->pos_x + a->offset_x + a->width > b->pos_x + b->offset_x && a->pos_y + a->offset_y < b->pos_y + b->offset_y + b->height && a->pos_y + a->offset_y + a->height >= b->pos_y + b->offset_y);
//};

void COL_PLShotsEnemies(Pl_Shots* shots, Enemies* enemies) {
    u8 ii;
    u8 jj;
    s8 aux;
    for (ii = 0; ii < MAX_PLAYER_SHOTS; ii++) {
        for(jj = 0; jj < MAX_ENEMIES; jj++) {
            if(shots->shot[ii].health > 0){
                if(enemies->enemy[jj].health > 0) {
                    if(collidePLShotEnemy(&shots->shot[ii], &enemies->enemy[jj])) {
                        aux = enemies->enemy[jj].health;
                        enemies->enemy[jj].health -= shots->shot[ii].health;
                        shots->shot[ii].health -= aux;
                        KLog_U2("Collision between shot ii = ", ii, " and enemy jj = ", jj);
                        KLog_f4("   > at shot x = ", shots->shot[ii].pos_x, " y = ", shots->shot[ii].pos_y, "; enemy x = ", enemies->enemy[jj].pos_x, " y = ", enemies->enemy[jj].pos_y);
                        KLog_S2("shot ", ii, " health at ", shots->shot[ii].health);
                        KLog_S2("enemy ", jj, " health at ", enemies->enemy[jj].health);
                    }
                }
            }
        }
    }
}



void COL_ENShotsPlayer(En_Shots* shots, Player* player) {
    u8 ii;
    for (ii = 0; ii < MAX_ENEMY_SHOTS; ii++) {
        if(shots->shot[ii].status == ALIVE) {
            if(collideENShotPlayer(&shots->shot[ii],player)) {
                player->health = 0;
            }
        }
    }
}

void COL_EnemiesPlayer(Enemies* enemies, Player* player) {
    u8 ii;
    for (ii = 0; ii < MAX_ENEMIES; ii++) {
        if(enemies->enemy[ii].status == ALIVE) {
            if(collideENPlayer(&enemies->enemy[ii], player)) {
                player->health = 0;
            }
        }
    }
}

//void enShotCollisions (Enemies* enemies, Shots* shots) {
//    int i = 0;
//    int j = 0;
//    for (i = 0; i < MAX_SHOTS; i++) {
//        for (j = 0; j < MAX_ENEMIES; j++) {
//            if (shots->playerShot[i].health > 0 && enemies->enemy[j].health > 0) {
//                if(collideEntities(&shots->playerShot[i], &enemies->enemy[j])) {
//                    enemies->enemy[j].health -= shots->playerShot[i].health;
//                    killEntity(&shots->playerShot[i]);
//                    shots->shotsOnScreen--;
//                }
//            }
//        }
//    }
//}
