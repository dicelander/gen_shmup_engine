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
#define PLAYER_EXPLOSION_LENGHT 55

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
//    KLog_U1("Shot has been killed succesfully index ", index);
//    KLog("tiro destruido");
};

void PL_killPlayer(Player* player) {
    player->health = 0;
    SPR_setVisibility(player->sprite,HIDDEN);
    SPR_releaseSprite(player->sprite);
    player->status = DEAD;
    player->timer = 0;
    player->width = 0;
    player->height = 0;
    player->offset_x = 0;
    player->offset_y = 0;
};


void PL_movePlayer(Player* player) {
    switch (player->status) {
        case ALIVE:
            if (player->health > 0) {
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
                if((player->vel_x != 0 || player->vel_y !=0)) {
                    addPosHistory(PL_getPosHistoryPtr(), player); //procurar um jeito melhor de fazer isso
                }
                SPR_setPosition(player->sprite, fix16ToInt(player->pos_x), fix16ToInt(player->pos_y));
            } else {
                PL_explode(player);
            }
            break;
        case EXPLOSION:
            if(player->timer < PLAYER_EXPLOSION_LENGHT) {
                player->timer++;
            } else {
                player->sprite->timer = 0;
                PL_killPlayer(player);
            }
            break;
        case DEAD:
            break;
    }
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
        shots->shot[ii].Action.move = NULL;
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
//                        KLog_U1("Player shot will be removed by moveShots on index ", ii);
                        PL_killShot(&shots->shot[ii], ii);
                        shots->pl_shotsonscreen--;
//                        KLog_U1("shotOnScreen now at ", shots->pl_shotsonscreen);
                    } else {
                        shots->shot[ii].pos_x += shots->shot[ii].vel_x;
                        shots->shot[ii].pos_y += shots->shot[ii].vel_y;
                        SPR_setPosition(shots->shot[ii].sprite, fix16ToInt(shots->shot[ii].pos_x), fix16ToInt(shots->shot[ii].pos_y));
                    }
                } else {
//                    KLog_U1("Shot will be killed due to health at index ii = ", ii);
                    PL_killShot(&shots->shot[ii], ii);
                    shots->pl_shotsonscreen--;
                }
            case DEAD:
                break;
        }
    }
}

void PL_explode(Player* player) {
    player->status = EXPLOSION;
    SPR_releaseSprite(player->sprite);
    player->sprite = SPR_addSprite(&pl_expl, fix16ToInt(player->pos_x), fix16ToInt(player->pos_y), TILE_ATTR(PAL1,0,0,0));
    player->timer = 0;
    player->width = 0;
    player->height = 0;
    player->offset_x = 0;
    player->offset_y = 0;
}

#define POSITION_HISTORY_SIZE 40

Pos_History* pos_hist_ptr;

void addPosHistory(Pos_History* history, Player* player) {
    history->pos_x[history->current] = player->pos_x + FIX16(12);
    history->pos_y[history->current] = player->pos_y + FIX16(16);
//    KLog_f2("added to history x:", history->pos_x[history->current], ", y:", history->pos_y[history->current]);
//    KLog_U1("at current: ", history-> current);
    history->current++;
    if (history->current == POSITION_HISTORY_SIZE) {
        history->current = 0;
    }
}

void PL_initPosHistory (Pos_History* history) {
    u8 ii;
    for (ii = 0; ii < POSITION_HISTORY_SIZE; ii++) {
        history->pos_x[ii] = 0;
        history->pos_y[ii] = 0;
    }
    history->current = 0;
    pos_hist_ptr = history;
}

Pos_History* PL_getPosHistoryPtr() {
    return pos_hist_ptr;
}

void PL_setPosHistoryPtr(Pos_History* history) {
    pos_hist_ptr = history;
}
