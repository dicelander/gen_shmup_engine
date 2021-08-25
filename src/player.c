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

void PL_setPlayerPtr(Player* player) {
    playerptr = player;
}

Player *PL_getPlayerPtr() {
    return playerptr;
}

static Pl_Shots *pl_shots_ptr;

Pl_Shots *PL_getShotsPtr() {
    return pl_shots_ptr;
}

void PL_setShotsPtr(Pl_Shots *shots) {
    pl_shots_ptr = shots;
}

void PL_killShot(Pl_Shot* shot, u16 index){
    shot->health = 0;
    SPR_setVisibility(shot->sprite,HIDDEN);
    SPR_releaseSprite(shot->sprite);
    shot->status = DEAD;
    KLog_U1("Shot has been killed succesfully index ", index);
//    KLog("tiro destruido");
};

void PL_movePlayer(Player* player) {
    
    if((player->vel_x != 0) & (player->vel_y != 0)) {
        player->pos_x += fix16Mul(player->vel_x, DIAGONAL45);
        player->pos_y += fix16Mul(player->vel_y, DIAGONAL45);
    } else {
        player->pos_x += player->vel_x;
        player->pos_y += player->vel_y;
    }
    
    if (fix16Add(player->pos_x, player->offset_x) < LEFT_EDGE) {
        player->pos_x = fix16Sub(LEFT_EDGE, player->offset_x);
    } else if (fix16Add(fix16Add(player->pos_x, player->offset_x), player->width) > RIGHT_EDGE) {
        player->pos_x = fix16Sub(RIGHT_EDGE, fix16Add(player->width, player->offset_x));
    }
    if (fix16Add(player->pos_y, player->offset_y) < TOP_EDGE) {
        player->pos_y = fix16Sub(TOP_EDGE, player->offset_y);
    }
    else if (fix16Add(fix16Add(player->pos_y, player->height), player->offset_y) > BOTTOM_EDGE) {
        player->pos_y = fix16Sub(BOTTOM_EDGE, fix16Add(player->height, player->offset_y));
    }
    
    SPR_setPosition(player->sprite, fix16ToInt(player->pos_x), fix16ToInt(player->pos_y));
}

void PL_initShots(Pl_Shots* shots) {
    u16 ii;
    for (ii=0; ii<MAX_PLAYER_SHOTS; ii++) {
        shots->shot[ii].pos_x = 0;
        shots->shot[ii].pos_y = 0;
        shots->shot[ii].offset_x = 0;
        shots->shot[ii].offset_y = 0;
        shots->shot[ii].width = 0;
        shots->shot[ii].height = 0;
        shots->shot[ii].vel_x = 0;
        shots->shot[ii].vel_y = 0;
        shots->shot[ii].health = 0;
        shots->shot[ii].sprite = NULL;
        shots->shot[ii].type = 0;
        shots->shot[ii].timer = 0;
        shots->shot[ii].direction = 0;
        shots->shot[ii].status = DEAD;
    }
    shots->pl_shotsonscreen = 0;
    pl_shots_ptr = shots;
}

void PL_moveShots(Pl_Shots* shots) {
    u16 ii = 0;
    for (ii = 0; ii < MAX_PLAYER_SHOTS; ii++) {
        switch (shots->shot[ii].status) {
            case ALIVE:
                if(shots->shot[ii].health > 0) {
                    if(fix16Add(shots->shot[ii].pos_y, shots->shot[ii].height) < TOP_EDGE || (shots->shot[ii].pos_x + shots->shot[ii].width) < LEFT_EDGE || shots->shot[ii].pos_x > RIGHT_EDGE) {
                        KLog_U1("Player shot will be removed by moveShots on index ", ii);
                        PL_killShot(&shots->shot[ii], ii);
                        shots->pl_shotsonscreen--;
                        KLog_U1("shotOnScreen now at ", shots->pl_shotsonscreen);
                    } else {
                        shots->shot[ii].pos_x += shots->shot[ii].vel_x;
                        shots->shot[ii].pos_y += shots->shot[ii].vel_y;
                        SPR_setPosition(shots->shot[ii].sprite, fix16ToInt(shots->shot[ii].pos_x), fix16ToInt(shots->shot[ii].pos_y));
                    }
                } else {
                    KLog_U1("Shot will be killed due to health at index ii = ", ii);
                    PL_killShot(&shots->shot[ii], ii);
                    shots->pl_shotsonscreen--;
                }
            case DEAD:
                break;
        }
    }
}
