//
//  player.c
//  gen_shmup
//
//  Created by Victor "dicelander" Sander on 20/08/21.
//

#define LEFT_EDGE FIX16(0)
#define RIGHT_EDGE FIX16(320)
#define TOP_EDGE FIX16(0)
#define BOTTOM_EDGE FIX16(224)
#define DIAGONAL45 0x2D //FIX16(0.71)

#include "../inc/player.h"
#include <player.h>

static Player *playerptr;

void setPointerPlayer(Player* player) {
    playerptr = player;
}

Player *getPointerPlayer() {
    return playerptr;
}

void movePlayer(Player* player) {
    
    if((player->vel_x != 0) & (player->vel_y != 0)) {
        player->pos_x += fix16Mul(player->vel_x, DIAGONAL45);
        player->pos_y += fix16Mul(player->vel_y, DIAGONAL45);
    } else {
        player->pos_x += player->vel_x;
        player->pos_y += player->vel_y;
    }
    
    if (fix16Add(player->pos_x, player->offset_x) < LEFT_EDGE) {
        player->pos_x = LEFT_EDGE - player->offset_x;
    } else if (fix16Add(fix16Add(player->pos_x, player->offset_x), player->width) > RIGHT_EDGE) {
        player->pos_x = RIGHT_EDGE - fix16Add(player->width, player->offset_x);
    }
    if (fix16Add(player->pos_y, player->offset_y) < TOP_EDGE) {
        player->pos_y = TOP_EDGE - player->offset_y;
    }
    else if (fix16Add(fix16Add(player->pos_y, player->height), player->offset_y) > BOTTOM_EDGE) {
        player->pos_y = BOTTOM_EDGE - fix16Add(player->height, player->offset_y);
    }
    
    SPR_setPosition(player->sprite, fix16ToInt(player->pos_x), fix16ToInt(player->pos_y));
}
