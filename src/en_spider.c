//
//  en_spider.c
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 28/08/21.
//

#include "../inc/en_spider.h"

void en_spider_move(Enemy* enemy, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    enemy->pos_x += enemy->vel_x;
    enemy->pos_y += enemy->vel_y;
    SPR_setPosition(enemy->sprite, fix16ToInt(enemy->pos_x), fix16ToInt(enemy->pos_y));
}


void en_spider_spawn(Enemies* enemies, const u8 type, s16 pos_x, s16 pos_y, const Behaviour* behaviour) {
    u16 i = 0;
    if (enemies->enemiesOnScreen < MAX_ENEMIES) {
        while (enemies->enemy[i].status != DEAD) {
            i++;
        }
        enemies->enemy[i].pos_x = FIX16(pos_x);
        enemies->enemy[i].pos_y = FIX16(pos_y);
        enemies->enemy[i].width = FIX16(24);
        enemies->enemy[i].height = FIX16(24);
        enemies->enemy[i].vel_x = 0;
        enemies->enemy[i].vel_y = 0;
        enemies->enemy[i].health = 4;
        enemies->enemy[i].status = ALIVE;
        enemies->enemy[i].sprite = SPR_addSprite(&enemy2,fix16ToInt(enemies->enemy[i].pos_x),fix16ToInt(enemies->enemy[i].pos_y),TILE_ATTR(PAL1,0,0,0));
        SPR_setDepth(enemies->enemy[i].sprite, SPR_MIN_DEPTH+1);
        //enemies->enemy[i].type = type;
        enemies->enemy[i].nextpatternstate = 0;
        enemies->enemy[i].timer = 0;
        enemies->enemy[i].pattern = behaviour;
        enemies->enemy[i].Action.move = &en_spider_move;
        enemies->enemy[i].Action.shoot = &en_spider_shoot;
        enemies->enemiesOnScreen++;
    }
}

void en_spider_setAnim(Enemy* spider, Action_Arg anim, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode) {
    SPR_setAnim(spider->sprite, (s16) anim.u16);
}

void en_spider_chargeShot(Enemy* spider, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode) {
    SPR_setAnim(spider->sprite, 1);
}

void en_spider_beginShot(Enemy* spider, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode) {
    SPR_setAnim(spider->sprite, 2);
}

void en_spider_shoot(Enemy* enemy, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    SPR_setAnim(enemy->sprite, 3);
    u16 ii;
    En_Shots *shots = EN_getShotsPtr();
    if (shots->en_shotsonscreen < MAX_ENEMY_SHOTS) {
        while (shots->shot[ii].status != DEAD) {
            ii++;
        }
        shots->shot[ii].status = ALIVE;
        shots->shot[ii].parent = enemy;
        shots->shot[ii].pos_x = enemy->pos_x+FIX16(8);
        shots->shot[ii].pos_y = enemy->pos_y+enemy->height;
        shots->shot[ii].vel_x = enemy->vel_x;
        shots->shot[ii].vel_y = enemy->vel_y;
        shots->shot[ii].width = FIX16(8);
        shots->shot[ii].height = FIX16(32);
        shots->shot[ii].health = 1;
        shots->shot[ii].timer = 0;
        shots->shot[ii].sprite = SPR_addSprite(&en_beam,fix16ToInt(shots->shot[ii].pos_x),fix16ToInt(shots->shot[ii].pos_y),TILE_ATTR(PAL1,0,FALSE,FALSE));
        SPR_setDepth(shots->shot[ii].sprite, SPR_MIN_DEPTH);
        shots->shot[ii].Action.move = &en_spider_mvShot;
        shots->en_shotsonscreen++;
    }
}

void en_spider_changeVelocity(Enemy* enemy, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg arg5) {
    enemy->vel_x = vel_x.fix16;
    enemy->vel_y = vel_y.fix16;
}

void en_spider_mvShot(En_Shot* shot, En_Shots* shots) {
    if (shot->parent->status != ALIVE) {
        EN_killShot(shot);
        shots->en_shotsonscreen--;
    } else {
        if (shot->timer == 2) {
            SPR_setAnim(shot->sprite, 1);
            if (shot->pos_y <= (BOTTOM_EDGE - shot->height)) {
                //basically the shot shoots another one.
                u16 ii = 0;
                if (shots->en_shotsonscreen < MAX_ENEMY_SHOTS) {
                    while (shots->shot[ii].status != DEAD) {
                        ii++;
                    }
                    shots->shot[ii].status = ALIVE;
                    shots->shot[ii].parent = shot;
                    shots->shot[ii].pos_x = shot->pos_x;
                    shots->shot[ii].pos_y = shot->pos_y+shot->height;
                    shots->shot[ii].vel_x = shot->vel_x;
                    shots->shot[ii].vel_y = shot->vel_y;
                    shots->shot[ii].width = FIX16(8);
                    shots->shot[ii].height = FIX16(32);
                    shots->shot[ii].health = 1;
                    shots->shot[ii].timer = 0;
                    shots->shot[ii].sprite = SPR_addSprite(&en_beam,fix16ToInt(shots->shot[ii].pos_x),fix16ToInt(shots->shot[ii].pos_y),TILE_ATTR(PAL1,0,FALSE,FALSE));
                    SPR_setDepth(shots->shot[ii].sprite, SPR_MIN_DEPTH);
                    shots->shot[ii].Action.move = &en_spider_mvShot;
                    shots->en_shotsonscreen++;
                }
            } /*else {
                shot->timer = 0;
            }*/
        }
        shot->vel_x = shot->parent->vel_x;
        shot->vel_y = shot->parent->vel_y;
        shot->pos_x += shot->vel_x;
        shot->pos_y += shot->vel_y;
//        KLog_f2("pos_x:", shot->pos_x, " pos_y:", shot->pos_y);
//        KLog_U2("pos_xU:", fix16ToInt(shot->pos_x), " pos_yU:", fix16ToInt(shot->pos_y));
//        KLog("Relative to parent:");
//        KLog_U2("pos_xU:", fix16ToInt(shot->pos_x)-fix16ToInt(shot->parent->pos_x), " pos_yU:",  fix16ToInt(shot->pos_y)-fix16ToInt(shot->parent->pos_y+shot->parent->height));
        
        //if (fix16ToInt(shot->pos_y)-fix16ToInt(shot->parent->pos_y+shot->parent->height) != 0)
        //if (shot->timer%2) SPR_setPalette(shot->sprite, PAL0); else SPR_setPalette(shot->sprite, PAL1);
        SPR_setPosition(shot->sprite, fix16ToInt(shot->pos_x), fix16ToInt(shot->pos_y));
//        if (SPR_isVisible(shot->sprite, FALSE)) { //flicker (for transparency)
//            SPR_setVisibility(shot->sprite, HIDDEN);
//        } else {
//            SPR_setVisibility(shot->sprite, VISIBLE);
//            SPR_setPosition(shot->sprite, fix16ToInt(shot->pos_x), fix16ToInt(shot->pos_y));
//        }
        shot->timer++;
    }
};

void en_spider_UpdateMvt(Enemy* spider, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode) {
    switch (mode.u16) {
        case 0:
            spider->pos_x += vel_x.fix16;
            spider->pos_y += vel_y.fix16;
            break;
        case 1:
            spider->pos_x = pos_x.fix16;
            spider->pos_y = pos_y.fix16;
            break;
        case 3:
            break;
        default:
            break;
    }
}

void en_spider_moveDeAcc(Enemy* spider, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode) {
    if (spider->vel_y > FIX16(-2.0)) {
        spider->vel_y += FIX16(-0.5);
    } else {
        spider->vel_y = FIX16(0);
        spider->Action.move = &en_spider_move;
    }
    KLog_f1("vel_y: ", spider->vel_y);
    spider->pos_x += spider->vel_x;
    spider->pos_y += spider->vel_y;
    SPR_setPosition(spider->sprite, fix16ToInt(spider->pos_x), fix16ToInt(spider->pos_y));
}

void en_spider_changeType(Enemy* spider, Action_Arg action, Action_Arg type, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    spider->Action.move = &en_spider_moveDeAcc;
    /*
    switch (action.u16) {
        case 0:
            switch (type.u16) {
                case 0:
                    spider->type.move = &en_spiderUpdateVel;
                    break;
                case 1:
                    break;
                default:
                    break;
            }
            break;
        case 1:
            switch (type.u16) {
                case 0:
                    spider->type.move = &en_spiderUpdateVel;
                    break;
            }
            break;
        case 2:
            switch (type.u16) {
                case 0:
                    spider->type.move = &en_spiderUpdateVel;
                    break;
                case 1:
                    break;
            }
            break;
    }
     */
}

void en_spider_kill(Enemy* spider, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    spider->health = 0;
    SPR_setVisibility(spider->sprite,HIDDEN);
    SPR_releaseSprite(spider->sprite);
    spider->status = DEAD;
}
