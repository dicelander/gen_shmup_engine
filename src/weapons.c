//
//  weapons.c
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 20/08/21.
//

#include <weapons.h>
#include "../inc/weapons.h"

void wpn_peaShooter(Pl_Shots* shots, Player* player){
//    KLog("Shot function called");
//    KLog_U1("shots->shotsOnScreen = ", shots->shotsOnScreen);
    int i = 0;
    if (shots->pl_shotsonscreen < MAX_PLAYER_SHOTS) {
        while (shots->shot[i].health > 0) {
            i++;
        }
//        KLog_U1("Shots Function [i]  = ", i);
        shots->shot[i].pos_x = player->pos_x+FIX16(8);
//        KLog_f1("player->pos_x = ", player->pos_x);
//        KLog_f1("shots->shot[i].pos_x = ", shots->shot[i].pos_x);
        shots->shot[i].pos_y = player->pos_y;
//        KLog_f1("player->pos_y = ", player->pos_y);
//        KLog_f1("shots->shot[i].pos_y = ", shots->shot[i].pos_y);
        shots->shot[i].width = FIX16(8);
//        KLog_f1("shots->shot[i].width = ", shots->shot[i].width);
        shots->shot[i].height = FIX16(8);
//        KLog_f1("shots->shot[i].height = ", shots->shot[i].height);
        //        reviveEntity(&shots[i]);
        shots->shot[i].vel_y = FIX16(-8);
        shots->shot[i].vel_x = 0;
        shots->shot[i].health = 1;
        shots->shot[i].sprite = SPR_addSprite(&peashtr,fix16ToInt(shots->shot[i].pos_x),fix16ToInt(shots->shot[i].pos_y),TILE_ATTR(PAL1,0,FALSE,FALSE));
        
        KLog_U2("Shot position on screen x = ", fix16ToInt(shots->shot[i].pos_x), ", y = ", fix16ToInt(shots->shot[i].pos_y));
        shots->pl_shotsonscreen++;
    }
    //    if (nShotsOnScreen < MAX_SHOTS) {
    //        while (shots[i] == TRUE) {
    //            i++;
    //        }
    //        shotPos[i][0] = (player.pos_x+12)%39;
    //        shotPos[i][1] = (player.pos_y+PLAYER_Y_OFFSET-2);
    //        shots0[i] = TRUE;
    //        nShotsOnScreen++;
    //    }
};
