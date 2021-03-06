//
//  enemies.c
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 23/08/21.
//

#include <enemies.h>
#include "../inc/enemies.h"

#define LEFT_EDGE FIX16(0)
#define RIGHT_EDGE FIX16(320)
#define TOP_EDGE FIX16(0)
#define BOTTOM_EDGE FIX16(224)

static Enemies *en_enemies_ptr;

Enemies *EN_getEnemiesPtr() {
    return en_enemies_ptr;
}

void EN_setEnemiesPtr(Enemies *enemies) {
    en_enemies_ptr = enemies;
}

static En_Shots *en_shots_ptr;

En_Shots *EN_getShotsPtr() {
    return en_shots_ptr;
}

void EN_setShotsPtr(En_Shots *shots) {
    en_shots_ptr = shots;
}

void EN_initShots(En_Shots *shots) {
    u16 ii;
    for (ii=0; ii<MAX_ENEMY_SHOTS; ii++) {
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
    shots->en_shotsonscreen = 0;
    en_shots_ptr = shots;
}

void EN_killEnemy(Enemy* e){
    e->health = 0;
    SPR_setVisibility(e->sprite,HIDDEN);
    SPR_releaseSprite(e->sprite);
    e->status = DEAD;
};

void EN_updateEnemies(Enemies *enemies){
    u16 ii = 0;
    for (ii = 0; ii < MAX_ENEMIES; ii++) {
        switch (enemies->enemy[ii].status) {
            case DEAD:
                break;
            case ALIVE:
                if(enemies->enemy[ii].health > 0) {
                    // método diferente de fazer a atualização dos inimigos, mais barato porém menos maleável.
                    /*
                    while(enemies->enemy[ii].timer == enemies->enemy[ii].pattern->actionframes[enemies->enemy[ii].nextpatternstate]) {
                        enemies->enemy[ii].pattern->actions[enemies->enemy[ii].nextpatternstate](&enemies->enemy[ii], enemies->enemy[ii].pattern->arg0[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg1[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg2[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg3[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg4[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg5[enemies->enemy[ii].nextpatternstate]);
                        enemies->enemy[ii].nextpatternstate++;
                    }
                     */
                    if(enemies->enemy[ii].timer == enemies->enemy[ii].pattern->actionframes[enemies->enemy[ii].nextpatternstate]) {
                        enemies->enemy[ii].pattern->actions[enemies->enemy[ii].nextpatternstate](&enemies->enemy[ii], enemies->enemy[ii].pattern->arg0[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg1[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg2[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg3[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg4[enemies->enemy[ii].nextpatternstate], enemies->enemy[ii].pattern->arg5[enemies->enemy[ii].nextpatternstate]);
                        enemies->enemy[ii].nextpatternstate++;
                        enemies->enemy[ii].timer = 0xFFFF;
                    }
                    enemies->enemy[ii].Action.move(&enemies->enemy[ii], (Action_Arg) (u16) 0, (Action_Arg) (u16) 0, (Action_Arg) (u16) 0, (Action_Arg) (u16) 0, (Action_Arg) (u16) 0, (Action_Arg) (u16) 0);
                    enemies->enemy[ii].timer++;
                } else if(enemies->enemy[ii].health <= 0) {
                    enemies->enemy[ii].status = EXPLOSION;
                    SPR_releaseSprite(enemies->enemy[ii].sprite);
                    enemies->enemy[ii].sprite = SPR_addSprite(&explos, fix16ToInt(enemies->enemy[ii].pos_x), fix16ToInt(enemies->enemy[ii].pos_y), TILE_ATTR(PAL1,0,0,0));
                    enemies->enemy[ii].timer = 0;
                    enemies->enemy[ii].width = 0;
                    enemies->enemy[ii].height = 0;
                    enemies->enemy[ii].offset_x = 0;
                    enemies->enemy[ii].offset_y = 0;
                }
                break;
            case EXPLOSION:
                if(enemies->enemy[ii].timer < EXPLOSION_LENGHT) {
                    enemies->enemy[ii].timer++;
                } else if(enemies->enemy[ii].timer == EXPLOSION_LENGHT) {
                    EN_killEnemy(&enemies->enemy[ii]);
                    enemies->enemiesOnScreen--;
                }
                break;
            default:
                break;
        }
    }
}

void EN_killShot(En_Shot* e){
    e->health = 0;
    SPR_setVisibility(e->sprite,HIDDEN);
    SPR_releaseSprite(e->sprite);
    e->status = DEAD;
};

void EN_moveShots(En_Shots *shots) {
    u16 i = 0;
    for (i = 0; i < MAX_ENEMY_SHOTS; i++) {
        if(shots->shot[i].status != DEAD) {
            shots->shot[i].Action.move(&shots->shot[i], shots);
        }
    }
}
