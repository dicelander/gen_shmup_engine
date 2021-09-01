//
//  en_spider.c
//  gen_shmupc
//
//  Created by Victor "dicelander" Sander on 28/08/21.
//

#include "../inc/en_spider.h"

void en_spiderSpawn(Enemies* enemies, const u8 type, s16 pos_x, s16 pos_y, const Behaviour* behaviour) {
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
        enemies->enemiesOnScreen++;
    }
}

void en_spiderShoot(Enemy* enemyptr, Action_Arg arg0, Action_Arg arg1, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
    u16 ii;
    En_Shots *shots = EN_getShotsPtr();
    Enemy* enemy = (Enemy *) enemyptr;
    if (shots->en_shotsonscreen < MAX_ENEMY_SHOTS) {
        while (shots->shot[ii].status != DEAD) {
            ii++;
        }
        shots->shot[ii].status = ALIVE;

        shots->shot[ii].pos_x = enemy->pos_x+FIX16(8);
        shots->shot[ii].pos_y = enemy->pos_y+enemy->height;
        shots->shot[ii].width = FIX16(8);
        shots->shot[ii].height = FIX16(32);
        shots->shot[ii].health = 1;
        shots->shot[ii].sprite = SPR_addSprite(&en_beam,fix16ToInt(shots->shot[ii].pos_x),fix16ToInt(shots->shot[ii].pos_y),TILE_ATTR(PAL1,0,FALSE,FALSE));
        SPR_setDepth(shots->shot[ii].sprite, SPR_MIN_DEPTH);
        shots->en_shotsonscreen++;
        }
}

void en_spiderChangeVelocity(Enemy* enemy, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg arg5) {
    enemy->vel_x = vel_x.fix16;
    enemy->vel_y = vel_y.fix16;
}

void en_spiderMvShot();

void en_spiderUpdateMvt(Enemy* spider, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode) {
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

void en_spiderUpdateVel(Enemy* spider, Action_Arg vel_x, Action_Arg vel_y, Action_Arg pos_x, Action_Arg pos_y, Action_Arg dir, Action_Arg mode) {
    spider->vel_x += FIX16(-1);
    spider->vel_y += FIX16(-1);
}

void en_spiderChangeTypeAction(Enemy* spider, Action_Arg action, Action_Arg type, Action_Arg arg2, Action_Arg arg3, Action_Arg arg4, Action_Arg arg5) {
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
}

Behaviour const spiderBehaviour = {
    .actions = {&en_spiderChangeVelocity, &en_spiderChangeVelocity, &en_spiderChangeVelocity, &en_spiderChangeVelocity, &en_spiderChangeVelocity, &en_spiderChangeVelocity, &en_spiderChangeVelocity},
    .actionframes = {0, 30, 40, 50, 60, 70, 80},
    .arg0 = {{.fix16 = FIX16(0)}, {.fix16 = FIX16(-0.71)}, {.fix16 = FIX16(-1)}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {.fix16 = FIX16(-0.71)}, {.fix16 = FIX16(0)}, {0}, {0}, {0}},
    .arg1 = {{.fix16 = FIX16(2)}, {.fix16 = FIX16(1.42)}, {.fix16 = FIX16(0)}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {.fix16 = FIX16(-1.42)}, {.fix16 = FIX16(-2)}, {0}, {0}, {0}},
    .arg2 = {{NULL}},
    .arg3 = {{NULL}},
    .arg4 = {{.u16 = ENEMY_DOWN},{.u16 = ENEMY_DOWN_LEFT},{.u16 = ENEMY_LEFT}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {.u16 = ENEMY_UP_LEFT}, {.u16 = ENEMY_UP}},
    .arg5 = {{NULL}},
};
